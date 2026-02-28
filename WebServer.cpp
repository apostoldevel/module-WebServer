#include "WebServer.hpp"
#include "apostol/application.hpp"

#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace apostol
{

WebServer::WebServer(Application& app)
    : doc_root_(app.settings().doc_root)
    , enabled_(app.module_enabled("WebServer"))
{
    load_allowed_origins(app.providers());
}

void WebServer::init_methods()
{
    add_method("GET",  [this](const HttpRequest& req, HttpResponse& resp) {
        do_get(req, resp, false);
    });
    add_method("HEAD", [this](const HttpRequest& req, HttpResponse& resp) {
        do_get(req, resp, true);
    });
}

void WebServer::do_get(const HttpRequest& req, HttpResponse& resp, bool head_only)
{
    // path is already stripped of query string by the HTTP parser
    const std::string& path_str = req.path;

    // Validate: absolute path, no ".." traversal (mirrors v1 DoGet)
    if (path_str.empty() || path_str.front() != '/' ||
        path_str.find("..") != std::string::npos)
    {
        resp.set_status(400, "Bad Request")
            .set_body("400 Bad Request", "text/plain");
        return;
    }

    // Build candidate list (try-files, mirrors v1 CWebServer::DoGet)
    std::vector<std::string> candidates;
    candidates.push_back(path_str);
    if (path_str.back() == '/')
        candidates.push_back(path_str + "index.html");
    else
        candidates.push_back(path_str + "/index.html");
    candidates.push_back("/index.html"); // SPA fallback

    for (const auto& candidate : candidates)
    {
        // Resolve against doc_root; strip leading '/' to make it relative
        fs::path file_path = doc_root_ / candidate.substr(1);
        if (fs::exists(file_path) && fs::is_regular_file(file_path))
        {
            if (serve_file(file_path, resp, head_only))
                return;
        }
    }

    resp.set_status(404, "Not Found")
        .set_body("404 Not Found", "text/plain");
}

} // namespace apostol
