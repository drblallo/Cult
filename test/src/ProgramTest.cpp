#include "gtest/gtest.h"
#include <atomic>
#include <memory>

#include "Engine.hpp"
#include "Program.hpp"
#include "SoutSink.hpp"
#include "TestUtils.hpp"
#include "TextFileDatabase.hpp"

class ProgramTest: public testing::Test
{
	public:
	virtual void SetUp() { utils::initLogger(false); }
	virtual void TearDown() {}
};

TEST_F(ProgramTest, programShouldLink)
{
	engine::Engine engine;
	std::atomic<bool> done(false);
	engine.start();
	engine.runLater([&done] {
		engine::TextFileDatabase dataBase;
		engine::Shader vShader(
				dataBase.get("resources/test/default.vert"), GL_VERTEX_SHADER);
		engine::Shader fShader(
				dataBase.get("resources/test/default.frag"), GL_FRAGMENT_SHADER);
		engine::Program p(vShader, fShader);
		EXPECT_TRUE(p.good());
		done.store(true);
	});

	waitUntil([&done] { return done.load(); });
}

TEST_F(ProgramTest, programShouldNotLinkIfBroken)
{
	engine::Engine engine;
	std::atomic<bool> done(false);
	engine.start();
	engine.runLater([&done] {
		engine::TextFileDatabase dataBase;
		engine::Shader vShader(
				dataBase.get("resources/test/default.vert"), GL_VERTEX_SHADER);
		engine::Shader fShader(
				dataBase.get("resources/test/default2.frag"), GL_FRAGMENT_SHADER);
		engine::Program p(vShader, fShader);
		EXPECT_FALSE(p.good());
		done.store(true);
	});

	waitUntil([&done] { return done.load(); });
}
