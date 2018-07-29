ADD_EXECUTABLE(runTest src/simpleTest.cpp src/SafeQueueTest.cpp)
TARGET_LINK_LIBRARIES(runTest PRIVATE gtest gtest_main LIB_UTILS debug gcov)
TARGET_INCLUDE_DIRECTORIES(runTest PUBLIC include PRIVATE src)
TARGET_COMPILE_FEATURES(runTest PUBLIC cxx_std_14)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

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
