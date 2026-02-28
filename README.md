[![ru](https://img.shields.io/badge/lang-ru-green.svg)](README.ru-RU.md)

Web Server
-

**Module** for [Apostol](https://github.com/apostoldevel/apostol) + [db-platform](https://github.com/apostoldevel/db-platform) — **Apostol CRM**[^crm].

Description
-
**WebServer** is an HTTP server module that serves static files and provides a web interface for Apostol-based applications.

- Serves static content from the `www/` directory (HTML, CSS, JavaScript, images, etc.).
- Provides [Swagger UI](https://swagger.io/tools/swagger-ui) for browsing and testing the REST API — available at [http://localhost:8080](http://localhost:8080) after Apostol starts.
- Handles HTTP `GET` and `HEAD` requests, mapping URL paths to files on disk.
- Supports SPA (Single Page Application) mode with try-files fallback to `index.html`.
- Returns a `404 Not Found` response for any path that does not match a file.
- Automatically handles CORS via `OPTIONS` preflight requests (inherited from `ApostolModule`).

The module runs as a long-lived **Worker** inside the Apostol worker process and shares the same `epoll`-based event loop as the PostgreSQL connection pool — no threads, no extra processes.

Installation
-
Follow the build and installation instructions for [Apostol](https://github.com/apostoldevel/apostol#build-and-installation).

[^crm]: **Apostol CRM** is an abstract term, not a standalone product. It refers to any project that uses both the [Apostol](https://github.com/apostoldevel/apostol) C++ framework and [db-platform](https://github.com/apostoldevel/db-platform) together through purpose-built modules and processes. Each framework can be used independently; combined, they form a full-stack backend platform.
