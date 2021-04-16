#include <server.hpp>
#include "config.hpp"

int main(int argc, char** argv) {
    std::string config_path = (argc > 1)? argv[1]: "httpd.conf";
    auto config = Config(config_path);

    Server server(config);
    server.start();
    return 0;
}
