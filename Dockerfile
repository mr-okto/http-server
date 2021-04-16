FROM ubuntu:latest
USER root

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get -y install g++ cmake libboost-all-dev

WORKDIR /src
COPY . /src

RUN cmake .
RUN make

COPY ./httpd.conf /etc/httpd.conf
COPY ./http-test-suite/httptest /var/www/html/httptest

EXPOSE 80

CMD ./http_server
