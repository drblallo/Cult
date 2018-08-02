//
// Created by massimo on 30/07/18.
//

#include <gtest/gtest.h>
#include <thread>

#include "Engine.hpp"
#include "TestUtils.hpp"

using namespace GEngine;

class EngineTest: public testing::Test
{
	virtual void SetUp()
	{
		Engine::getEngine().start();
		waitUntil([]() { return Engine::getEngine().isRunning();});
	}

	virtual void TearDown()
	{
		Engine::getEngine().stop();
		waitUntil([]() { return Engine::getEngine().isRunning();}, false);
	}
};

TEST_F(EngineTest, engineShouldStart)
{
	EXPECT_EQ(Engine::getEngine().isRunning(), true);
}

TEST_F(EngineTest, engineAndEnvironementShouldRestart)
{
	Engine::getEngine().stop();

	waitUntil([]() { return Engine::getEngine().isRunning();}, false);

	Engine::terminate();
	Engine::getEngine().start();

	waitUntil([]() { return Engine::getEngine().isRunning();});
}
