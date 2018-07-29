cmake_minimum_required(VERSION 3.9)
project(Cult)

add_subdirectory(googletest)
add_subdirectory(test)
add_subdirectory(game)
add_subdirectory(g3log)
add_subdirectory(glfw)

ADD_EXECUTABLE(Cult main.cpp)
TARGET_LINK_LIBRARIES(Cult PRIVATE g3logger LIB_ENGINE debug gcov)
TARGET_COMPILE_FEATURES(Cult PUBLIC cxx_std_14)
TARGET_COMPILE_OPTIONS(
        runTest PRIVATE
        "$<$<CONFIG:DEBUG>:--coverage>"
        "$<$<CONFIG:DEBUG>:-W>"
        "$<$<CONFIG:DEBUG>:-Wall>"
        "$<$<CONFIG:DEBUG>:-g>"
        "$<$<CONFIG:DEBUG>:-O0>"
        "$<$<CONFIG:DEBUG>:-fno-inline>"
        "$<$<CONFIG:DEBUG>:-fno-inline-small-functions>"
        "$<$<CONFIG:DEBUG>:-fno-default-inline>"
)