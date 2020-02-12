cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp server/server.cpp server/server.hpp server/fork_server.cpp server/fork_server.hpp server/thread_server.cpp server/thread_server.hpp server/config.cpp server/config.hpp server/details.hpp)