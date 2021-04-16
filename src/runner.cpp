#include "runner.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include "response.hpp"
#include "request.hpp"

Runner::Runner(const std::string& doc_root, boost::asio::io_service& service)
        : doc_root_m(doc_root), socket_m(service) {}


void Runner::handle_request(ThreadsCounter& counter) {
    try {
        Request r;
        boost::asio::streambuf buf;
        boost::asio::read_until(socket_m, buf, "\r\n\r\n");
        std::string r_data((std::istreambuf_iterator<char>(&buf)),
                           std::istreambuf_iterator<char>());
        if (!r.parse(r_data.c_str())) {
            std::cerr << "Unable to process request: " << r_data << std::endl;
        }
        else {
            std::string response = Response::get_response(r.get_method(),
                                                          r.get_protocol(),
                                                                   doc_root_m + r.get_path());
            boost::asio::write(socket_m, boost::asio::buffer(response), boost::asio::transfer_all());
        }
        socket_m.close();
    } catch(std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
    try {
        socket_m.close();
    } catch(boost::system::system_error& e) {
        std::cerr << "Unable to close socket: " << e.what() << std::endl;
    }
    counter.dec();
}

boost::asio::ip::tcp::socket &Runner::get_socket() {
    return socket_m;
}
