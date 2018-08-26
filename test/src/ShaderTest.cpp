#include "gtest/gtest.h"
#include <atomic>
#include <glad/glad.h>
#include <memory>

#include "Engine.hpp"
#include "Shader.hpp"
#include "SoutSink.hpp"
#include "TestUtils.hpp"
#include "TextFileDatabase.hpp"

class ShaderTest: public testing::Test
{
	public:
	std::unique_ptr<engine::Engine> engin;
	virtual void SetUp()
	{
		utils::initLogger(false);
		engin.reset(new engine::Engine());
		engin->start();
	}
	virtual void TearDown() {}
};

TEST_F(ShaderTest, testShaderShouldLoad)
{
	std::atomic<bool> done(false);
	engin->runLater([&done] {
		engine::TextFileDatabase dataBase;
		auto s = std::make_unique<engine::Shader>(
				dataBase.get("./resources/test/default.frag"), GL_FRAGMENT_SHADER);
		EXPECT_TRUE(s->good());
		done.store(true);
	});

	waitUntil([&done] { return done.load(); });
}

TEST_F(ShaderTest, testShaderShouldNotLoadIfShaderIsBroken)
{
	std::atomic<bool> done(false);
	engin->runLater([&done] {
		auto s = std::make_unique<engine::Shader>("mestUp", GL_FRAGMENT_SHADER);
		EXPECT_TRUE(!s->good());
		done.store(true);
	});

	waitUntil([&done] { return done.load(); });
}
