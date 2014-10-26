cmake_minimum_required(VERSION 2.8)

project(tk_client)

set(SOURCE_EXE main.cpp)
set(SOURCE_LIB tk_network_client.cpp)

add_library(tk_network_client STATIC ${SOURCE_LIB})

add_executable(client ${SOURCE_EXE})

target_link_libraries(client tk_network_client)