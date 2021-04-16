#ifndef HTTP_SERVER_RUNNER_HPP
#define HTTP_SERVER_RUNNER_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "threads_counter.hpp"

class Runner: public std::enable_shared_from_this<Runner> {
public:
    explicit Runner(const std::string& doc_root, boost::asio::io_service& service);
    void handle_request(ThreadsCounter& counter);
    boost::asio::ip::tcp::socket& get_socket();
private:
    std::string doc_root_m;
    boost::asio::ip::tcp::socket socket_m;
};

#endif //HTTP_SERVER_RUNNER_HPP
