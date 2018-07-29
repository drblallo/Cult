ADD_LIBRARY(LIB_UTILS STATIC)
TARGET_LINK_LIBRARIES(LIB_UTILS PRIVATE g3logger debug gcov)
TARGET_INCLUDE_DIRECTORIES(LIB_UTILS PRIVATE src PUBLIC include)
TARGET_COMPILE_FEATURES(LIB_UTILS PUBLIC cxx_std_14)
TARGET_SOURCES(LIB_UTILS PRIVATE src/ConsumerThread.cpp include/ConsumerThread.hpp include/SafeQueue.hpp)

TARGET_COMPILE_OPTIONS(
        LIB_UTILS PRIVATE
        "$<$<CONFIG:DEBUG>:--coverage>"
        "$<$<CONFIG:DEBUG>:-W>"
        "$<$<CONFIG:DEBUG>:-Wall>"
        "$<$<CONFIG:DEBUG>:-g>"
        "$<$<CONFIG:DEBUG>:-O0>"
        "$<$<CONFIG:DEBUG>:-fno-inline>"
        "$<$<CONFIG:DEBUG>:-fno-inline-small-functions>"
        "$<$<CONFIG:DEBUG>:-fno-default-inline>"
        )
