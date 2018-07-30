//
// Created by massimo on 30/07/18.
//

#include <gtest/gtest.h>
#include <ConsumerThread.hpp>
#include <thread>

class ConsumerThreadStub : public utils::ConsumerThread {
 public:
  ConsumerThreadStub() : ConsumerThread(), markCalled(false), stopCalled(false) {}
  virtual ~ConsumerThreadStub() {}
  bool markCalled;
  bool stopCalled;
  void appendToQueue() {append([this](){markCalled = true;});}

 private:
  virtual void onStop() {stopCalled = true;}

};

class ConsumerThreadTest : public testing::Test {
 public:
  ConsumerThreadStub thread;
};


TEST_F(ConsumerThreadTest, atCreationShouldNotBeRunning) {
  EXPECT_EQ(false, thread.isRunning());
  EXPECT_EQ(false, thread.wasStarted());
}

TEST_F(ConsumerThreadTest, operationAppendedWillWait) {
  thread.appendToQueue();
  EXPECT_EQ(false, thread.markCalled);
}

TEST_F(ConsumerThreadTest, operationAppendedWillBeProcessed) {
  thread.appendToQueue();
  thread.start(false);
  EXPECT_EQ(true, thread.markCalled);
}

TEST_F(ConsumerThreadTest, canBeStoppedWhenDetached) {
  thread.start(true);
  thread.appendToQueue();
  int a(0);
  while (!thread.markCalled && a++ < 100)
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  thread.stop();

  a = 0;
  while (!thread.stopCalled && a++ < 100)
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
}

TEST_F(ConsumerThreadTest, cannotBeStartedTwice) {
  thread.start(true);
  thread.start(true);
}

TEST_F(ConsumerThreadTest, cannotBeStoppedTwice) {
  thread.start(true);
  thread.stop();
  thread.stop();
}

TEST_F(ConsumerThreadTest, cannotBeStoppedAtStart) {
  thread.stop();
}

TEST_F(ConsumerThreadTest, canBeDestroyedWhileRunning) {
  auto t = new ConsumerThreadStub();
  t->start(true);
  delete t;
}

TEST_F(ConsumerThreadTest, canBeDestroyedWhileStopped) {
  thread.start(true);
  thread.stop();
  while (!thread.hasEnded())
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
}

TEST_F(ConsumerThreadTest, canBeDestroyedOnStack) {
  for (int a = 0; a < 2; a++) {
    ConsumerThreadStub t;
    t.start(false);
  }
}

TEST_F(ConsumerThreadTest, baseObjectCanBeDestroyed) {
  auto t = new utils::ConsumerThread();
  t->start(true);
  delete t;
}
