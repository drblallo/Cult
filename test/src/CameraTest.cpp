#include "gtest/gtest.h"
#include <memory>

#include "Camera.hpp"

class CameraTest: public testing::Test
{
	public:
	virtual void SetUp() { camera.reset(new engine::Camera(100, 100)); }
	virtual void TearDown() {}

	std::unique_ptr<engine::Camera> camera;
};

#include <iostream>
TEST_F(CameraTest, projectionShouldBeCorrect)
{
	glm::vec4 v(-0.2, 0, -0.1, 1);
	v = camera->getWorldToScreen() * v;
	EXPECT_EQ(v.x / v.w, -2);
	EXPECT_EQ(v.y / v.w, 0);
	EXPECT_EQ(v.z / v.w, -1);

	v = glm::vec4(0, -50, -100, 1);
	v = camera->getWorldToScreen() * v;

	EXPECT_EQ(v.x / v.w, 0);
	EXPECT_EQ(v.y / v.w, -0.5);
	EXPECT_EQ(v.z / v.w, 1);
}
