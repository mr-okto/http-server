#include "request.hpp"

#include <sstream>

bool Request::parse(const char* data) {
    std::istringstream iss (data);
    return (iss >> method_m && iss >> path_m && iss >> protocol_m);
}

const std::string &Request::get_method() {
    return method_m;
}

const std::string &Request::get_path() {
    return path_m;
}

const std::string &Request::get_protocol() {
    return protocol_m;
}
