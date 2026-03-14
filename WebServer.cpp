#include "WebServer.hpp"
#include "apostol/application.hpp"

#include "apostol/file_utils.hpp"
#include "apostol/http_utils.hpp"

namespace apostol
{

WebServer::WebServer(Application& app)
    : logger_(app.logger())
    , sites_(app.sites())
    , doc_root_(app.settings().doc_root)
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

std::filesystem::path WebServer::resolve_root(const HttpRequest& req) const
{
    auto host = get_host(req);
    {
        if (const auto* site = sites_.find(host))
            if (!site->root.empty())
                return site->root;
    }
    return doc_root_;
}

void WebServer::do_get(const HttpRequest& req, HttpResponse& resp, bool head_only)
{
    // path is already stripped of query string by the HTTP parser
    const std::string& path_str = req.path;

    // Validate: absolute path, no ".." traversal (mirrors v1 DoGet)
    if (path_str.front() != '/' || !is_safe_path(path_str))
    {
        resp.set_status(400, "Bad Request")
            .set_body("400 Bad Request", "text/plain");
        return;
    }

    try_files(resolve_root(req), req, resp, head_only);
}

} // namespace apostol
