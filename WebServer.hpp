#pragma once

#include "apostol/apostol_module.hpp"

#include <filesystem>
#include <string_view>

namespace apostol
{

class Application;

// ─── WebServer ────────────────────────────────────────────────────────────────
//
// Serves static files from doc_root.
//
// Supported methods:
//   GET     — serve file; try-files fallback to index.html / SPA root
//   HEAD    — headers only, no body (Content-Length reflects actual file size)
//   OPTIONS — handled automatically by ApostolModule (returns Allow header)
//   others  — 405 Method Not Allowed (handled automatically by ApostolModule)
//
// Path rules (mirroring v1 CWebServer::DoGet):
//   • Must begin with '/'
//   • Must not contain ".."
//   • Query string is stripped before resolving the path
//
class WebServer final : public ApostolModule
{
public:
    explicit WebServer(Application& app);

    std::string_view name()    const override { return "WebServer"; }
    bool             enabled() const override { return enabled_; }

protected:
    void init_methods() override;

private:
    void do_get(const HttpRequest& req, HttpResponse& resp, bool head_only);

    std::filesystem::path doc_root_;
    bool                  enabled_;
};

} // namespace apostol
