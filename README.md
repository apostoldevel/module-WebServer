[![ru](https://img.shields.io/badge/lang-ru-green.svg)](README.ru-RU.md)

Web Server
-

**Module** for **Apostol CRM**[^crm].

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
Follow the build and installation instructions for [Апостол (C++20)](https://github.com/apostoldevel/libapostol#build-and-installation).

[^crm]: **Apostol CRM** — шаблон-проект построенный на фреймворках [A-POST-OL](https://github.com/apostoldevel/libapostol) (C++20) и [PostgreSQL Framework for Backend Development](https://github.com/apostoldevel/db-platform).
