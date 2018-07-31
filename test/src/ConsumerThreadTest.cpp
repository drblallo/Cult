//
// Created by massimo on 30/07/18.
//

#include <gtest/gtest.h>
#include <ConsumerThread.hpp>
#include <thread>

using namespace utils;

class ConsumerThreadTest : public testing::Test {
 public:
  ConsumerThreadTest() : thread(), markCalled(false) {}
  ConsumerThread thread;
  std::atomic<bool> markCalled;
  void append() {
    thread.runLater([this]() { markCalled.store(true); });
  }
};


TEST_F(ConsumerThreadTest, atCreationShouldNotBeRunning) {
  EXPECT_EQ(false, thread.isRunning());
}

TEST_F(ConsumerThreadTest, operationAppendedWillWait) {
  append();
  EXPECT_EQ(false, markCalled.load());
}

TEST_F(ConsumerThreadTest, operationAppendedWillBeProcessed) {
  thread.start();
  append();

  while (!markCalled.load()) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }
  EXPECT_EQ(true, markCalled.load());
}

TEST_F(ConsumerThreadTest, canBeStoppedWhenDetached) {
  thread.start();
  append();
  while (!markCalled.load())
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));

  EXPECT_EQ(true, markCalled.load());
  thread.stop();

  while (thread.isRunning())
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  EXPECT_EQ(false, thread.isRunning());
}

TEST_F(ConsumerThreadTest, cannotBeStartedTwice) {
  thread.start();
  thread.start();
}

TEST_F(ConsumerThreadTest, cannotBeStoppedTwice) {
  thread.start();
  thread.stop();
  thread.stop();
}

TEST_F(ConsumerThreadTest, cannotBeStoppedAtStart) {
  thread.stop();
}

TEST_F(ConsumerThreadTest, canBeDestroyedWhileRunning) {
  auto t = new ConsumerThread();
  t->start();
  delete t;
}

TEST_F(ConsumerThreadTest, canBeDestroyedWhileStopped) {
  thread.start();
  thread.stop();
  while (thread.isRunning())
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  EXPECT_EQ(false, thread.isRunning());
}

TEST_F(ConsumerThreadTest, canBeDestroyedOnStack) {
  for (int a = 0; a < 2; a++) {
    ConsumerThread t;
    t.start();
  }
}

TEST_F(ConsumerThreadTest, baseObjectCanBeDestroyed) {
  auto t = new utils::ConsumerThread();
  t->start();
  delete t;
}

TEST_F(ConsumerThreadTest, cannotBeBlockStoppedFromHisOwnThread) {
  thread.start();
  thread.runLater([this]() { thread.blockingStop(); markCalled.store(true); });

  while (!markCalled.load()) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }
  EXPECT_EQ(true, markCalled.load());
  EXPECT_EQ(thread.isRunning(), true);
}

TEST_F(ConsumerThreadTest, canBeBlockedFronHisOwnThread) {
  thread.start();
  thread.runLater([this]() { thread.stop(); });

  while (thread.isRunning()) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }
  EXPECT_EQ(thread.isRunning(), false);
}

TEST_F(ConsumerThreadTest, startCleansQueue) {
  append();
  thread.start();
  int a = 0;
  while (a++ < 100 && !markCalled.load()) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }
  EXPECT_EQ(false, markCalled.load());
}

TEST_F(ConsumerThreadTest, canBeRestarted) {
  thread.start();
  append();

  while (!markCalled.load()) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }
  EXPECT_EQ(true, markCalled.load());

  thread.blockingStop();
  EXPECT_EQ(false, thread.isRunning());
  markCalled.store(false);

  thread.start();
  append();

  while (!markCalled.load()) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }
  EXPECT_EQ(true, markCalled.load());
}

TEST_F(ConsumerThreadTest, testPreAndPostFunction) {
  int a(0);
  int b(0);
  ConsumerThread consumer([&a]() {a++;}, [&b] {b++;});
  consumer.start();
  while (a == 0)
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  EXPECT_EQ(1, a);

  consumer.stop();
  while (b == 0)
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  EXPECT_EQ(1, b);

}



