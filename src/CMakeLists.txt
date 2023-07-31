cmake_minimum_required(VERSION 3.0)
project(MyProject)

add_executable(cilent cilent.c)
add_executable(server server.c)

target_link_libraries(cilent pthread)
target_link_libraries(server pthread)
