cmake_minimum_required(VERSION 3.0)

project(opencv)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(open ./src/main.cpp)

target_link_libraries(open ${OpenCV_LIBS})