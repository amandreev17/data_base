cmake_minimum_required(VERSION 3.4)
project(data)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(GLOB SRC_SRC "sources/data_base.cpp")

add_executable(data sources/data_base.cpp)