#include "gtest/gtest.h"
#include <atomic>
#include <memory>

#include "Engine.hpp"
#include "Program.hpp"
#include "ShaderProgramDatabase.hpp"
#include "SoutSink.hpp"
#include "TestUtils.hpp"

class ProgramDatabaseTest: public testing::Test
{
	public:
	std::unique_ptr<engine::ShaderProgramDatabase> database;
	virtual void SetUp()
	{
		utils::initLogger(false);
		database.reset(new engine::ShaderProgramDatabase);
	}
	virtual void TearDown() {}
};

TEST_F(ProgramDatabaseTest, missingFragmentShaderShouldThrow)
{
	EXPECT_THROW(
			database->get("./resources/test/default.vert", "missing.frag"),
			std::invalid_argument);
}

TEST_F(ProgramDatabaseTest, goodShaderShouldCompile)
{
	engine::Engine engine;
	engine.start();
	std::atomic<bool> terminated(false);
	engine.runLater([this, &terminated] {
		std::shared_ptr<engine::Program> t = database->get(
				"./resources/test/default.vert", "./resources/test/default.frag");
		EXPECT_EQ(true, t->good());
		terminated.store(true);
	});
	waitUntil([&terminated] { return terminated.load(); });
}

TEST_F(ProgramDatabaseTest, missingVertexShaderShouldThrow)
{
	EXPECT_THROW(
			database->get("missingShader.vert", "missingShader.frag"),
			std::invalid_argument);
}
