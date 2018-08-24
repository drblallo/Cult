//
// Created by massimo on 30/07/18.
//

#include <gtest/gtest.h>
#include <thread>

#include "Engine.hpp"
#include "SoutSink.hpp"
#include "TestUtils.hpp"

using namespace engine;

class EngineTest: public testing::Test
{
	public:
	engine::Engine engine;
	virtual void SetUp()
	{
		EXPECT_EQ(false, Engine::isInitialized());
		utils::initLogger(false);
		engine.start();
		waitUntil([this]() { return engine.isRunning(); });
		waitUntil(
				[]() { return Engine::isInitialized(); },
				true,
				100,
				std::chrono::milliseconds(100));
	}

	virtual void TearDown()
	{
		EXPECT_EQ(true, Engine::isInitialized());
		engine.stop();
		waitUntil([this]() { return engine.isRunning(); }, false);
		waitUntil(
				[]() { return Engine::isInitialized(); },
				false,
				100,
				std::chrono::milliseconds(100));
	}
};

TEST_F(EngineTest, engineShouldStart) { EXPECT_EQ(engine.isRunning(), true); }

TEST_F(EngineTest, engineAndEnvironementShouldRestart)
{
	engine.stop();

	waitUntil([this]() { return engine.isRunning(); }, false);

	engine.start();

	waitUntil([this]() { return engine.isRunning(); });
	waitUntil(
			[]() { return Engine::isInitialized(); },
			true,
			100,
			std::chrono::milliseconds(100));
}

TEST_F(EngineTest, canCreateMultipleEngines)
{
	engine::Engine engine2;
	engine2.start();

	waitUntil([this]() { return engine.isRunning(); });
	engine::Engine otherEngine;
	otherEngine.start();
}

TEST_F(EngineTest, engineGoingOutOfScopeShouldBeDestroyed)
{
	engine::Engine engine2;
	engine2.start();
}
