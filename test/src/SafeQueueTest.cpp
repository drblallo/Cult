//
// Created by massimo on 29/07/18.
//
#include <gtest/gtest.h>
#include "SafeQueue.hpp"

class SafeQueueTest : public testing::Test {
 public:
  utils::SafeQueue<int> queue;
  virtual void SetUp() {}
  virtual void TearDown() {}
};


TEST_F(SafeQueueTest, constructorShouldCreateEmpty) {
  EXPECT_TRUE(queue.empty());
}

TEST_F(SafeQueueTest, elementsShouldBeReturnedInOrder) {
  for (int a = 0; a < 5; a++)
    queue.offer(a);

  for (int a = 0; a < 5; a++)
    EXPECT_EQ(a, queue.poll());
}

