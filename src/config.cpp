#include "config.hpp"
#include <fstream>
#include <sstream>

Config::Config(const std::string &f_conf): Config() {
    this->parse(f_conf);
}

void Config::parse(const std::string &f_conf) {
    std::ifstream cfg(f_conf);
    std::string line;
    while (std::getline(cfg, line)) {
        std::istringstream buf_stream(line);
        std::string arg;
        buf_stream >> arg;
        if (arg == "Listen") {
            buf_stream >> port_m;
        } else if (arg == "thread_limit") {
            buf_stream >> thread_limit_m;
        } else if (arg == "document_root") {
            buf_stream >> document_root_m;
        }
    }
    cfg.close();
}

std::string Config::get_root() const {
    return document_root_m;
}

unsigned int Config::get_port() const {
    return port_m;
}

unsigned int Config::get_thread_limit() const {
    return thread_limit_m;
}

