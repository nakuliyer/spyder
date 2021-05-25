cmake_minimum_required(VERSION 3.17)
project(spyder)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS -I/usr/local/include)

add_executable(spyder main.cpp src/spyder.cc src/bg.cc src/card.cc src/const.cc src/pile.cc src/pile.h)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(spyder ${SDL2_LIBRARIES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
