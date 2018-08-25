message("COMPILING TESTS")
ADD_EXECUTABLE(runTest src/simpleTest.cpp src/SafeQueueTest.cpp src/ConsumerThreadTest.cpp src/EngineTest.cpp src/TestUtils.cpp src/Transform3DTest.cpp src/TreeTest.cpp src/RendererTest.cpp)
TARGET_LINK_LIBRARIES(runTest PRIVATE gtest gtest_main utils engine)
TARGET_INCLUDE_DIRECTORIES(runTest PUBLIC include PRIVATE src)
TARGET_COMPILE_FEATURES(runTest PUBLIC cxx_std_14)

compile_options(runTest)

if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CULT_TSAN)
	message("--enabling death test")
	TARGET_COMPILE_DEFINITIONS(runTest PUBLIC CULT_DEATH_TEST)	
elseif()
	message("--death test disabled")
endif()

message("END COMPILING TEST")
TARGET_SOURCES(runTest PRIVATE src/RenderObjectTest)
TARGET_SOURCES(runTest PRIVATE src/CameraTest)
