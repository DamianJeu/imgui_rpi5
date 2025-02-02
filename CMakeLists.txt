cmake_minimum_required(VERSION 3.10)
project(myApp)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(imgui)


add_executable(myApp main.cpp)


target_link_libraries(myApp PRIVATE imgui)
