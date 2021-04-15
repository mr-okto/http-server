cmake_minimum_required(VERSION 3.19)
project(http_server)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS system filesystem thread)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_executable(http_server src/main.cpp src/Config.cpp)

target_link_libraries(http_server ${Boost_LIBRARIES})
