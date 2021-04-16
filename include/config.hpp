#ifndef HTTP_SERVER_CONFIG_HPP
#define HTTP_SERVER_CONFIG_HPP

#include <string>

class Config {
public:
    explicit Config() = default;
    explicit Config(const std::string &f_conf);
    void parse(const std::string &f_conf);
    [[nodiscard]] std::string get_root() const;
    [[nodiscard]] unsigned int get_port() const;
    [[nodiscard]] unsigned int get_thread_limit() const;
private:
    unsigned int port_m = 80;
    unsigned int thread_limit_m = 4;
    std::string document_root_m = "/var/www/html";
};


#endif //HTTP_SERVER_CONFIG_HPP
