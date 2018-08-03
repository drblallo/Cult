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
		Engine::start();
		waitUntil([]() { return Engine::isRunning(); });
	}

	virtual void TearDown()
	{
		Engine::stop();
		waitUntil([]() { return Engine::isRunning(); }, false);
	}
};

TEST_F(EngineTest, engineShouldStart) { EXPECT_EQ(Engine::isRunning(), true); }

TEST_F(EngineTest, engineAndEnvironementShouldRestart)
{
	Engine::stop();

	waitUntil([]() { return Engine::isRunning(); }, false);

	Engine::terminate();
	Engine::start();

	waitUntil([]() { return Engine::isRunning(); });
}
