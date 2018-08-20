//
// Created by massimo on 03/08/18.
//

#include <gtest/gtest.h>

#include "Transform3D.hpp"

using namespace engine;
class Transform3DTest: public testing::Test
{
	public:
	Transform3D transform;
	virtual void SetUp(){};
	virtual void TearDown(){};
};

TEST_F(Transform3DTest, defaultShouldBeIdentity)
{
	auto proj = transform.getProjection();
	EXPECT_EQ(proj, glm::mat4(1));
}

TEST_F(Transform3DTest, defaultTranslationShouldBeVectorZero)
{
	EXPECT_EQ(transform.getTranslation(), glm::vec3(0));
}

TEST_F(Transform3DTest, defaultRotationShouldBeZero)
{
	EXPECT_EQ(transform.getRotation(), glm::vec3(0));
}

TEST_F(Transform3DTest, defaultScalingShouldBeVectorOne)
{
	EXPECT_EQ(transform.getScale(), glm::vec3(1));
}

TEST_F(Transform3DTest, vectorSumShouldBeAdditive)
{
	transform.translate(1, 10, 100);
	EXPECT_NEAR(transform.getTranslation().x, 1, 0.1f);
	EXPECT_NEAR(transform.getTranslation().y, 10, 0.1f);
	EXPECT_NEAR(transform.getTranslation().z, 100, 0.1f);

	transform.translate(glm::vec3(-1, -15, 20));
	EXPECT_NEAR(transform.getTranslation().x, 0, 0.1f);
	EXPECT_NEAR(transform.getTranslation().y, -5, 0.1f);
	EXPECT_NEAR(transform.getTranslation().z, 120, 0.1f);
}

TEST_F(Transform3DTest, scalingShouldBeAdditive)
{
	transform.scale(1, 10, 100);
	EXPECT_NEAR(transform.getScale().x, 2, 0.1f);
	EXPECT_NEAR(transform.getScale().y, 11, 0.1f);
	EXPECT_NEAR(transform.getScale().z, 101, 0.1f);

	transform.scale(glm::vec3(-1, -15, 20));
	EXPECT_NEAR(transform.getScale().x, 1, 0.1f);
	EXPECT_NEAR(transform.getScale().y, -4, 0.1f);
	EXPECT_NEAR(transform.getScale().z, 121, 0.1f);
}

TEST_F(Transform3DTest, rotationShouldBeAdditive)
{
	transform.rotate(0.1f, 1.0f, 1.5f);
	EXPECT_NEAR(transform.getRotation().x, 0.1, 0.1f);
	EXPECT_NEAR(transform.getRotation().y, 1, 0.1f);
	EXPECT_NEAR(transform.getRotation().z, 1.5, 0.1f);

	transform.rotate(glm::vec3(-0.1f, -0.5f, 0.3f));
	EXPECT_NEAR(transform.getRotation().x, 0, 0.1f);
	EXPECT_NEAR(transform.getRotation().y, 0.5f, 0.1f);
	EXPECT_NEAR(transform.getRotation().z, 1.8, 0.1f);
}

TEST_F(Transform3DTest, projectionAndInvertedProjectionShouldBeIdentity)
{
	transform.rotate(1, 2, 3);
	transform.scale(2, 4, 5);
	transform.translate(3, 4, 5);

	glm::mat4 matrix(
			transform.getProjection() * transform.getInvertedProjection());

	glm::vec4 vectorOut(1);
	vectorOut = transform.getProjection() * vectorOut;

	EXPECT_NE(vectorOut.x, 1);
	EXPECT_NE(vectorOut.y, 1);
	EXPECT_NE(vectorOut.z, 1);

	vectorOut = matrix * glm::vec4(1);

	EXPECT_NEAR(vectorOut.x, 1, 0.1f);
	EXPECT_NEAR(vectorOut.y, 1, 0.1f);
	EXPECT_NEAR(vectorOut.z, 1, 0.1f);
}

TEST_F(Transform3DTest, projectionMakeSense)
{
	transform.rotate(1, 1, 1);
	transform.scale(1, 1, 1);
	transform.translate(1, 1, 1);

	glm::vec4 vectorOut(transform.getProjection() * glm::vec4(0, 0, 0, 1));
	EXPECT_NEAR(vectorOut.x, 1, 0.1f);
	EXPECT_NEAR(vectorOut.y, 1, 0.1f);
	EXPECT_NEAR(vectorOut.z, 1, 0.1f);
}

TEST_F(Transform3DTest, setTranslationShouldSet)
{
	transform.setTranslation(1, 1, 1);
	EXPECT_EQ(transform.getTranslation().x, 1);
	EXPECT_EQ(transform.getTranslation().y, 1);
	EXPECT_EQ(transform.getTranslation().z, 1);
}

TEST_F(Transform3DTest, setRotationSouldSet)
{
	transform.setRotation(0.5f, 0.5f, 0.5f);
	EXPECT_EQ(transform.getRotation().x, 0.5f);
	EXPECT_EQ(transform.getRotation().y, 0.5f);
	EXPECT_EQ(transform.getRotation().z, 0.5f);
}

TEST_F(Transform3DTest, setScaleShouldSet)
{
	transform.setScale(2, 2, 2);
	EXPECT_EQ(transform.getScale().x, 2);
	EXPECT_EQ(transform.getScale().y, 2);
	EXPECT_EQ(transform.getScale().z, 2);
}
