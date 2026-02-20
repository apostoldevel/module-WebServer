[![ru](https://img.shields.io/badge/lang-ru-green.svg)](https://github.com/apostoldevel/module-WebServer/blob/master/README.ru-RU.md)

Web Server
-
**WebServer** — a module for [Apostol](https://github.com/apostoldevel/apostol).

Description
-
**WebServer** is an HTTP server module that serves static files and provides a web interface for Apostol-based applications.

- Serves static content from the `www/` directory (HTML, CSS, JavaScript, images, etc.).
- Provides [Swagger UI](https://swagger.io/tools/swagger-ui) for browsing and testing the REST API — available at [http://localhost:8080](http://localhost:8080) after Apostol starts.
- Handles HTTP `GET` requests and maps URL paths to files on disk.
- Returns a `404 Not Found` response for any path that does not match a file.

The module runs as a long-lived **Worker** inside the Apostol worker process and shares the same `epoll`-based event loop as the PostgreSQL connection pool — no threads, no extra processes.

Installation
-
Follow the build and installation instructions for [Apostol](https://github.com/apostoldevel/apostol#build-and-installation).
