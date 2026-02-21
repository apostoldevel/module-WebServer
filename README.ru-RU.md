[![en](https://img.shields.io/badge/lang-en-green.svg)](https://github.com/apostoldevel/module-WebServer/blob/master/README.md)

Веб-сервер
-
**WebServer** — модуль для [Apostol](https://github.com/apostoldevel/apostol) + [db-platform](https://github.com/apostoldevel/db-platform) — **Apostol CRM**[^crm].

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

[^crm]: **Apostol CRM** — абстрактный термин, а не самостоятельный продукт. Он обозначает любой проект, в котором совместно используются фреймворк [Apostol](https://github.com/apostoldevel/apostol) (C++) и [db-platform](https://github.com/apostoldevel/db-platform) через специально разработанные модули и процессы. Каждый фреймворк можно использовать независимо; вместе они образуют полноценную backend-платформу.