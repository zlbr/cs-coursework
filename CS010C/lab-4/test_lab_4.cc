#include <gtest/gtest.h>

#include "stack_vector.h"
#define NO_MAIN  // This prevents main() from being included
#include "q1-1.cc"
#include "q1-2.cc"
#include "q2.cc"
#undef NO_MAIN

// Test Suite for Q1.1
TEST(StackSortTest, BasicSort) {
  Stack<int> s;
  s.Push(3);
  s.Push(1);
  s.Push(2);

  EXPECT_EQ(s.Size(), 3);  // stack is full but unsorted

  Stack<int> sorted = Sort(s);

  EXPECT_EQ(sorted.Top(), 1);  // Smallest on top
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 2);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 3);
  sorted.Pop();

  EXPECT_EQ(sorted.Size(), 0);  // empty stack
}

TEST(SackSortTest, SortEmpty) {
  Stack<int> s;
  Stack<int> sorted = Sort(s);

  EXPECT_EQ(sorted.Size(), 0);  // empty stack
}

TEST(SackSortTest, SingleElementSort) {
  Stack<int> s;
  s.Push(1);

  Stack<int> sorted = Sort(s);

  EXPECT_EQ(sorted.Size(), 1);
  EXPECT_EQ(sorted.Top(), 1);
}

TEST(SackSortTest, SortNegatives) {
  Stack<int> s;
  s.Push(-100);
  s.Push(500);
  s.Push(100);
  s.Push(-500);

  EXPECT_EQ(s.Size(), 4);  // stack is full but unsorted

  Stack<int> sorted = Sort(s);

  EXPECT_EQ(sorted.Top(), -500);  // Smallest on top
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), -100);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 100);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 500);
  sorted.Pop();

  EXPECT_EQ(sorted.Size(), 0);  // empty stack
}

TEST(SackSortTest, SortDupes) {
  Stack<int> s;
  s.Push(100);
  s.Push(500);
  s.Push(100);

  EXPECT_EQ(s.Size(), 3);  // stack is full but unsorted

  Stack<int> sorted = Sort(s);

  EXPECT_EQ(sorted.Top(), 100);  // Smallest on top
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 100);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 500);
  sorted.Pop();

  EXPECT_EQ(sorted.Size(), 0);  // empty stack
}

// Test suite for Q1.2
TEST(StackDeleteTest, NormalArray) {
  Stack<int> s1;

  // fill s1 with data
  std::vector<int> v{59, 24, 49, 63, 41};
  for (auto i : v) s1.Push(i);

  // remove the middle item
  DeleteMiddleElement(s1, s1.Size());

  EXPECT_EQ(s1.Top(), 41);
  s1.Pop();
  EXPECT_EQ(s1.Top(), 63);
  s1.Pop();
  EXPECT_EQ(s1.Top(), 24);
  s1.Pop();
  EXPECT_EQ(s1.Top(), 59);
  s1.Pop();
}

TEST(StackDeleteTest, EvenArray) {
  Stack<int> s1;

  // fill s1 with data
  std::vector<int> v{24, 49, 63, 41};
  for (auto i : v) s1.Push(i);

  // remove the middle item
  DeleteMiddleElement(s1, s1.Size());

  EXPECT_EQ(s1.Top(), 41);
  s1.Pop();
  EXPECT_EQ(s1.Top(), 63);
  s1.Pop();
  EXPECT_EQ(s1.Top(), 24);
  s1.Pop();
}

TEST(StackDeleteTest, SingleElement) {
  Stack<int> s1;

  s1.Push(1738);

  // remove the middle item
  DeleteMiddleElement(s1, s1.Size());

  EXPECT_EQ(s1.Size(), 0);
}

// Test suite for Q2
TEST(TestQueue, BasicQueue) {
  Queue<int> q;

  // fill queue with data
  std::vector<int> v{59, 24, 49, 63, 41};
  for (auto i : v) q.Push(i);

  // q is now back-> 41, 63, 49, 24, 59 <-front

  EXPECT_EQ(q.Pop(), 59);
  EXPECT_EQ(q.Pop(), 24);
  EXPECT_EQ(q.Pop(), 49);
  EXPECT_EQ(q.Pop(), 63);
  EXPECT_EQ(q.Pop(), 41);
}

TEST(TestQueue, MultipleOps) {
  Queue<int> q;

  // fill queue with data
  std::vector<int> v{59, 24, 49, 63, 41};
  for (auto i : v) q.Push(i);

  // q is now back-> 23, 41, 63, 49, 24, 59 <-front

  EXPECT_EQ(q.Pop(), 59);

  q.Push(23);

  EXPECT_EQ(q.Pop(), 24);
  EXPECT_EQ(q.Pop(), 49);
  EXPECT_EQ(q.Pop(), 63);
  EXPECT_EQ(q.Pop(), 41);

  q.Push(64);

  EXPECT_EQ(q.Pop(), 23);
  EXPECT_EQ(q.Pop(), 64);
}

TEST(TestQueue, EmptyQueueOperation) {
  Queue<int> q;

  q.Push(41);

  EXPECT_EQ(q.Pop(), 41);
  EXPECT_EQ(q.Size(), 0);

  q.Push(23);

  EXPECT_EQ(q.Pop(), 23);
  EXPECT_EQ(q.Size(), 0);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
