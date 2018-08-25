#include "gtest/gtest.h"
#include <memory>

#include "RenderObject.hpp"

class RenderObjectTest: public testing::Test
{
	public:
	std::unique_ptr<engine::RenderObject> ogg;

	virtual void SetUp() { ogg.reset(new engine::RenderObject()); }
	virtual void TearDown() {}
};

TEST_F(RenderObjectTest, defaultTransformShouldBeIdentity)
{
	glm::vec4 v(10, 10, 10, 1);
	v = ogg->getTransform().getProjection() * v;
	EXPECT_EQ(v, glm::vec4(10, 10, 10, 1));
}
