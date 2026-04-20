#include <gtest/gtest.h>
#include "deque.h"

TEST(Deque, Empty) {
  Deque<int> dq;

  /* Should be fully empty */
  EXPECT_EQ(dq.Empty(), true);
  EXPECT_EQ(dq.Size(), 0);
  EXPECT_THROW(dq.PopFront(), std::exception);

  // TODO: Add more tests for empty deque behavior
  // For example, test that Front(), Back(), PopFront(), PopBack() throw exceptions

}

TEST(Deque, DoubleInsertionBack) {
  Deque<int> dq;

  /* Test some insertions at back */
  dq.PushBack(23);
  dq.PushBack(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq.Back(), 42);
  // TODO: Add more tests for PushBack behavior

}

TEST(Deque, DoubleInsertionBackFront) {
  Deque<int> dq;

  /* Test some insertions at back and front */
  dq.PushBack(23);
  dq.PushFront(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq.Back(), 23);

  // TODO: Add more tests for mixed Push operations

}

// TODO: Add more comprehensive test cases
// Suggestions:
// - Test PopFront and PopBack operations
// - Test operator[] for various positions
// - Test Clear() method
// - Test ShrinkToFit() method
// - Test exception handling for invalid operations
// - Test with different data types (not just int)
// - Test edge cases (single item, full capacity, etc.)
// - Test that operations maintain correct complexity

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
