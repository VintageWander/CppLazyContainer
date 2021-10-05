cmake_minimum_required(VERSION 3.21)
project(lazyContainer)

set(CMAKE_CXX_STANDARD 17)

add_library(lazy SHARED
            lazyContainer.h
            lazyContainer.cpp)

add_executable(lazyContainer main.cpp)
target_include_directories(lazy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lazyContainer PRIVATE lazy)
