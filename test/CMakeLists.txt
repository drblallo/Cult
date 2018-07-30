message("COMPILING TESTS")
ADD_EXECUTABLE(runTest src/simpleTest.cpp src/SafeQueueTest.cpp src/ConsumerThreadTest.cpp src/EngineTest.cpp)
TARGET_LINK_LIBRARIES(runTest PRIVATE gtest gtest_main LIB_UTILS LIB_ENGINE)
TARGET_INCLUDE_DIRECTORIES(runTest PUBLIC include PRIVATE src)
TARGET_COMPILE_FEATURES(runTest PUBLIC cxx_std_14)

debug_compile_options(runTest)

message("END COMPILING TEST")