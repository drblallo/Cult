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
  void appendToQueue() { runLater([this]() { markCalled = true; });}
  void appendTermination() { runLater([this]() { terminateNow(); });}

 private:
  virtual void onStop() {stopCalled = true;}

};

class ConsumerThreadTest : public testing::Test {
 public:
  ConsumerThreadStub thread;
};


TEST_F(ConsumerThreadTest, atCreationShouldNotBeRunning) {
  EXPECT_EQ(false, thread.isRunning());
}

TEST_F(ConsumerThreadTest, operationAppendedWillWait) {
  thread.appendToQueue();
  EXPECT_EQ(false, thread.markCalled);
}

TEST_F(ConsumerThreadTest, operationAppendedWillBeProcessed) {
  thread.start();
  thread.appendToQueue();

  int a = 0;
  while (a++ < 100 && !thread.markCalled) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }
  EXPECT_EQ(true, thread.markCalled);
}

TEST_F(ConsumerThreadTest, canBeStoppedWhenDetached) {
  thread.start();
  thread.appendToQueue();
  int a(0);
  while (!thread.markCalled && a++ < 100)
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));

  EXPECT_EQ(true, thread.markCalled);
  thread.stop();

  a = 0;
  while (!thread.stopCalled && a++ < 100)
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  EXPECT_EQ(true, thread.stopCalled);
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
  auto t = new ConsumerThreadStub();
  t->start();
  delete t;
}

TEST_F(ConsumerThreadTest, canBeDestroyedWhileStopped) {
  thread.start();
  thread.stop();
  int a = 0;
  while (thread.isRunning() && a++ < 100)
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  EXPECT_EQ(false, thread.isRunning());
}

TEST_F(ConsumerThreadTest, canBeDestroyedOnStack) {
  for (int a = 0; a < 2; a++) {
    ConsumerThreadStub t;
    t.start();
  }
}

TEST_F(ConsumerThreadTest, baseObjectCanBeDestroyed) {
  auto t = new utils::ConsumerThread();
  t->start();
  delete t;
}


TEST_F(ConsumerThreadTest, testInternalTermination) {
  thread.appendTermination();
  thread.start();

  int a = 0;
  while (a++ < 100 && !thread.isRunning()) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(10));
  }
  EXPECT_EQ(false, thread.markCalled);
}


