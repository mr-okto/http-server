#include "response.hpp"
#include <filesystem>
#include <fstream>
#include <cstring>

#define BUF_SIZE 1024

std::string Response::get_response(const std::string& method,
                                   const std::string& version, std::string url) {
    std::stringstream resp_ss;
    resp_ss << version << ' ';
    std::stringstream headers_ss;
    headers_ss << "Server: nginx\r\n"
        << "Date: " << get_date() << "\r\n"
        << "Connection: Closed\r\n";
    std::string headers = headers_ss.str();
    int resp_code;
    resp_ss << get_status(method, url, headers, resp_code) << headers << "\r\n";
    std::string response =  resp_ss.str();
    if (method == "HEAD") {
        return response;
    }
    if (resp_code == 200) {
        std::ifstream file(url.c_str(), std::ios::in | std::ios::binary);
        char buf[BUF_SIZE];
        while (file.read(buf, sizeof(buf)).gcount() > 0) {
            response.append(buf, file.gcount());
        }
    }
    return response;
}

std::string Response::decode_url(const char *src) {
    std::string uri;
    while (*src) {
        if (*src == '%' && isxdigit(*(src + 1)) && isxdigit(*(src + 2))) {
            char buf[3];
            memcpy(buf, src + 1, 2);
            std::stringstream ss;
            ss << std::hex << buf;
            int character;
            ss >> character;
            uri.push_back(static_cast<char>(character));
            src += 3;
        } else if (*src == '+') {
            uri.push_back(' ');
            src++;
        } else {
            uri.push_back(*src++);
        }
    }
    return uri;
}


std::string Response::get_status(const std::string& method, std::string& url,
                                 std::string& headers, int& resp_code) {
    if (method != "GET" && method != "HEAD") {
        return "405 Method Not Allowed\r\n";
    }
    size_t q_params = url.find('?');
    if (q_params != std::string::npos) {
        url = url.substr(0, q_params);
    }
    url = decode_url(url.data());
    size_t last_slash_index = url.find_last_of('/');

    if (url.find("../") != std::string::npos) {
        resp_code = 403;
        return "403 Forbidden\r\n";
    }
    if (!std::filesystem::exists(url)) {
        resp_code = 404;
        return "404 Not Found\r\n";
    }
    if (last_slash_index == url.length() - 1) {
        url += "index.html";
    }
    if (!std::filesystem::exists(url)) {
        resp_code = 403;
        return "403 Forbidden\r\n";
    }

    size_t ext_index = url.find_last_of('.');
    std::string content_type = get_content_type(url.substr(ext_index + 1, url.length() - ext_index));
    std::stringstream hstream;
    hstream << "Content-Type: " << content_type << "\r\n"
            << "Content-Length: " << std::filesystem::file_size(url) << "\r\n";
    headers.append(hstream.str());
    resp_code = 200;
    return "200 OK\r\n";
}

std::string Response::get_content_type(const std::string& ext) {
    if (ext == "html") {
        return "text/html";
    }
    if (ext == "css") {
        return "text/css";
    }
    if (ext == "js") {
        return "application/javascript";
    }
    if (ext == "jpg") {
        return "image/jpeg";
    }
    if (ext == "jpeg") {
        return "image/jpeg";
    }
    if (ext == "png") {
        return "image/png";
    }
    if (ext == "gif") {
        return "image/gif";
    }
    if (ext == "swf") {
        return "application/x-shockwave-flash";
    }
    if (ext == "txt") {
        return "text/plain";
    }
    return "";
}

std::string Response::get_date() {
    std::time_t timer = std::time(nullptr);
    char buf[BUF_SIZE];
    auto timeNow = std::strftime(buf, sizeof(buf),
                                 "%a, %d %b %Y %H:%M:%S GMT",
                                 std::localtime(&timer));
    return std::string(buf, timeNow);
}
