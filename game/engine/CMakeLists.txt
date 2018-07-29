ADD_LIBRARY(LIB_ENGINE STATIC)
TARGET_LINK_LIBRARIES(LIB_ENGINE PRIVATE glfw g3logger debug gcov)
TARGET_INCLUDE_DIRECTORIES(LIB_ENGINE PRIVATE src PUBLIC include)
TARGET_COMPILE_FEATURES(LIB_ENGINE PUBLIC cxx_std_14)
TARGET_SOURCES(LIB_ENGINE PRIVATE include/Window.hpp include/Engine.hpp src/Engine.cpp src/Window.cpp)
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
