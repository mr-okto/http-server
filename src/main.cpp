#include <server.hpp>
#include <iostream>
#include "config.hpp"

int main(int argc, char** argv) {
    std::string config_path = (argc > 1)? argv[1]: "/etc/httpd.conf";
    auto config = Config(config_path);
    std::cout << "Server launch at :" << config.get_port() << std::endl;
    Server server(config);
    server.start();
    return 0;
}
