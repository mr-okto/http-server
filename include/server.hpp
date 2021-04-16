#ifndef HTTP_SERVER_SERVER_HPP
#define HTTP_SERVER_SERVER_HPP


#include <boost/system/error_code.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <shared_mutex>
#include "config.hpp"
#include "runner.hpp"

class Server {
public:
    explicit Server(const Config& conf);
    void start();

private:
    void register_client();
    void accept_handler(const boost::system::error_code &error);

    const Config& config_m;
    ThreadsCounter threads_counter_m;
    boost::asio::io_service ioservice_m;
    boost::asio::ip::tcp::acceptor acceptor_m;
    std::shared_ptr<Runner> conn_handler_m;
};


#endif //HTTP_SERVER_SERVER_HPP
