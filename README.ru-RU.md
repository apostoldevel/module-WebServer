[![en](https://img.shields.io/badge/lang-en-green.svg)](https://github.com/apostoldevel/module-WebServer/blob/master/README.md)

Веб-сервер
-
**WebServer** — модуль для [Апостол](https://github.com/apostoldevel/apostol).

Описание
-
**WebServer** — модуль HTTP-сервера, который раздаёт статические файлы и обеспечивает веб-интерфейс для приложений на базе Апостол.

- Раздаёт статическое содержимое из директории `www/` (HTML, CSS, JavaScript, изображения и т. д.).
- Предоставляет [Swagger UI](https://swagger.io/tools/swagger-ui) для просмотра и тестирования REST API — доступен по адресу [http://localhost:8080](http://localhost:8080) после запуска Апостол.
- Обрабатывает HTTP-запросы `GET` и сопоставляет URL-пути с файлами на диске.
- Возвращает ответ `404 Not Found` для любого пути, не совпадающего с файлом.

Модуль работает как долгоживущий **Worker** внутри рабочего процесса Апостол и разделяет единый цикл событий на основе `epoll` с пулом соединений PostgreSQL — без потоков, без дополнительных процессов.

Установка
-
Следуйте указаниям по сборке и установке [Апостол](https://github.com/apostoldevel/apostol#build-and-installation).
