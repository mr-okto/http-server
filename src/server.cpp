#include <thread>
#include <iostream>
#include "server.hpp"

Server::Server(const Config &conf)
        : config_m(conf), ioservice_m(), threads_counter_m(conf.get_thread_limit()),
          acceptor_m(ioservice_m,
                     boost::asio::ip::tcp::endpoint(
                             boost::asio::ip::tcp::v4(), conf.get_port())) {
    register_client();
}

void Server::start() {
    ioservice_m.run();
}

void Server::register_client() {
    conn_handler_m = std::make_shared<Runner>(config_m.get_root(), ioservice_m);
    acceptor_m.async_accept(
            conn_handler_m->get_socket(),
            [this](auto && PH1) { accept_handler(std::forward<decltype(PH1)>(PH1)); }
    );
}

void Server::accept_handler(const boost::system::error_code &error) {
    if (error) {
        std::cerr << "Accept error: " << error.message() << std::endl;
        return;
    }
    threads_counter_m.inc();
    std::thread(std::bind(&Runner::handle_request, conn_handler_m,
                           std::ref(threads_counter_m))).detach();
    register_client();
}
