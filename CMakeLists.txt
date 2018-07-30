include(debug_compile_options.cmake)
cmake_minimum_required(VERSION 3.9)
project(Cult)

add_subdirectory(googletest)
add_subdirectory(test)
add_subdirectory(game)
add_subdirectory(g3log)
add_subdirectory(glfw)

message("COMPILING CULT")
ADD_EXECUTABLE(Cult main.cpp)
TARGET_LINK_LIBRARIES(Cult PRIVATE g3logger LIB_ENGINE)
TARGET_COMPILE_FEATURES(Cult PUBLIC cxx_std_14)

debug_compile_options(Cult)

message("END COMPILING CULT")
