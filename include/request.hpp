#ifndef HTTP_SERVER_REQUEST_HPP
#define HTTP_SERVER_REQUEST_HPP


#include <string>

class Request {
public:
    explicit Request() = default;
    bool parse(const char* data);

    const std::string& get_method();
    const std::string& get_path();
    const std::string& get_protocol();
private:
    std::string method_m;
    std::string path_m;
    std::string protocol_m;
};


#endif //HTTP_SERVER_REQUEST_HPP
