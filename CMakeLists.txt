cmake_minimum_required(VERSION 3.9)
project(Cult)

add_subdirectory(googletest)
add_subdirectory(test)
add_subdirectory(game)
add_subdirectory(g3log)
add_subdirectory(glfw)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cult main.cpp)
TARGET_LINK_LIBRARIES(Cult g3logger)
