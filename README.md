# http-server

## Веб-сервер для отдачи статики с диска


## Запуск
```
git clone git@github.com:mr-okto/http-server.git
cd http-server
docker build -t http-server .
docker run -p 8000:80 http-server
```
## Конфигурация
httpd.conf
```
Listen 80 # port to listen to 
thread_limit 256  # maximum simultaneous connections (for blocking servers)
document_root /var/www/html
```
