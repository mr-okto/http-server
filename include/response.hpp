#ifndef HTTP_SERVER_RESPONSE_HPP
#define HTTP_SERVER_RESPONSE_HPP

#include <vector>
#include <string>

class Response {
public:
    Response() = default;
    static std::string get_response(const std::string& method,
                                    const std::string& version, std::string url);

private:
    static std::string decode_url(const char *src);
    static std::string get_status(const std::string& method, std::string& raw_url,
                                  std::string& headers, int& resp_code);
    static std::string get_date();
    static std::string get_content_type(const std::string& ext);
};


#endif //HTTP_SERVER_RESPONSE_HPP
