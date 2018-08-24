#include "gtest/gtest.h"

#include "Renderer.hpp"
#include "SoutSink.hpp"

using namespace engine;
class RendererTest: public testing::Test
{
	public:
	std::unique_ptr<engine::Renderer> renderer;
	RenderObjectHandle getRoot() const { return renderer->getRenderObjectRoot(); }
	virtual void SetUp()
	{
		utils::initLogger(false);
		renderer.reset(new Renderer());
	}
	virtual void TearDown() {}
};

TEST_F(RendererTest, rendererShouldHaveAStartingChild)
{
	EXPECT_TRUE(getRoot().get() != nullptr);
}

TEST_F(RendererTest, addingObjectsShouldAddThemToRoot)
{
	auto t = renderer->add(std::make_unique<RenderObject>());
	EXPECT_EQ(getRoot().getChildCount(), 1);
	EXPECT_EQ(getRoot().getChild(0).get(), t.get());
}

TEST_F(RendererTest, objectCanBeRemoved)
{
	auto t = renderer->add(std::make_unique<RenderObject>());
	renderer->remove(t);
	EXPECT_EQ(getRoot().getChildCount(), 0);
}

TEST_F(RendererTest, parentCanBeSet)
{
	RenderObjectHandle h(renderer->add(std::make_unique<RenderObject>()));
	RenderObjectHandle h2(renderer->add(std::make_unique<RenderObject>()));

	EXPECT_EQ(getRoot().getChildCount(), 2);
	h.setParent(h2);
	EXPECT_EQ(getRoot().getChildCount(), 1);
	EXPECT_EQ(h.getChildCount(), 0);
	EXPECT_EQ(h2.getChildCount(), 1);
}

TEST_F(RendererTest, rendererCanBeMoved)
{
	RenderObjectHandle h(renderer->add(std::make_unique<RenderObject>()));
	Renderer r(std::move(*renderer.get()));

	EXPECT_EQ(r.getRenderObjectRoot().getChildCount(), 1);
	EXPECT_EQ(r.getRenderObjectRoot().getChild(0).get(), h.get());
}

#ifdef CULT_DEATH_TEST
TEST_F(RendererTest, cannotSetParentFromOtherRenderer)
{
	Renderer r;
	RenderObjectHandle h(r.add(std::make_unique<RenderObject>()));

	RenderObjectHandle h2(renderer->add(std::make_unique<RenderObject>()));

	EXPECT_DEBUG_DEATH(h2.setParent(h), ".*");
}
#endif
