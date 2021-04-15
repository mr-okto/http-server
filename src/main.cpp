#include <iostream>
#include "Config.hpp"

int main(int argc, char** argv) {
    std::string config_path = "httpd.conf";
    if (argc > 1) {
        config_path = argv[1];
    }
    auto config = Config(config_path);
    std::cout << "Config port: " << config.get_port()
        << ", root: " << config.get_root()
        << ", thread_limit: " <<config.get_thread_limit();
    return 0;
}
