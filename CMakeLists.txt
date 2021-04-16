cmake_minimum_required(VERSION 3.10.2)
project(http_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS} include)

add_executable(http_server src/main.cpp src/config.cpp src/runner.cpp src/response.cpp src/server.cpp src/request.cpp src/threads_counter.cpp)

target_link_libraries(http_server ${Boost_LIBRARIES})
