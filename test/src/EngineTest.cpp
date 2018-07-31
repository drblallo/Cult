//
// Created by massimo on 30/07/18.
//

#include "Engine.hpp"
#include <gtest/gtest.h>
#include <thread>

using namespace GEngine;

class EngineTest : public testing::Test {


  virtual void SetUp() {
    Engine::getEngine().start();
    int a = 0;
    while (!Engine::getEngine().isRunning() && a++ < 100)
      std::this_thread::sleep_for(std::chrono::milliseconds(10));

    EXPECT_EQ(Engine::getEngine().isRunning(), true);
  }

  virtual void TearDown() {
    Engine::getEngine().stop();
    int a = 0;
    while (Engine::getEngine().isRunning() && a++ < 100)
      std::this_thread::sleep_for(std::chrono::milliseconds(10));

    EXPECT_EQ(Engine::getEngine().isRunning(), false);
  }

};

TEST_F(EngineTest, engineShouldStart) {
  EXPECT_EQ(Engine::getEngine().isRunning(), true);
}

TEST_F(EngineTest, engineAndEnvironementShouldRestart) {
  Engine::getEngine().stop();

  int a = 0;
  while (Engine::getEngine().isRunning() && a++ < 100)
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

  EXPECT_EQ(Engine::getEngine().isRunning(), false);

  Engine::terminate();

  Engine::getEngine().start();
  a = 0;
  while (!Engine::getEngine().isRunning() && a++ < 100)
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

  EXPECT_EQ(Engine::getEngine().isRunning(), true);
}

