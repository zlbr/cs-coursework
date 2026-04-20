#include <gtest/gtest.h>  // there may be a red line under this
// if you do not have gtest installed locally.
// if you are using the cs010c container,
// you may disregard any errors from the previous line on local
#include "list_doubly_linked.h"

TEST(List, SizeEqZero) {
  ListDoublyLinked<int> l;
  ASSERT_EQ(l.Size(), 0);
}

// get element
TEST(List, GetElement) {
  ListDoublyLinked<int> l;
  l.Insert(10, 0);
  l.Insert(20, 1);
  l.Insert(15, 1);  // 10, 15, 20

  ASSERT_EQ(l.Size(), 3);
  ASSERT_EQ(l.Get(0), 10);
  ASSERT_EQ(l.Get(1), 15);
  ASSERT_EQ(l.Get(2), 20);
}

// insert
TEST(List, InsertElement) {
  ListDoublyLinked<int> l;
  l.Insert(11, 0);
  l.Insert(22, 0);  // 22, 11

  ASSERT_EQ(l.Size(), 2);
  ASSERT_EQ(l.Get(0), 22);
  ASSERT_EQ(l.Get(1), 11);
}

TEST(List, NewSuite) {
  ListDoublyLinked<int> l;
  l.Insert(100, 0);
  l.Insert(50, 0);  // 22, 11

  ASSERT_EQ(l.Size(), 2);
  ASSERT_EQ(l.Get(1), 100);
  ASSERT_EQ(l.Get(0), 50);

  l.Insert(200, 2);
  ASSERT_EQ(l.Size(), 3);
  ASSERT_EQ(l.Get(2), 200);

  l.Insert(30, 1);
  ASSERT_EQ(l.Size(), 4);
  ASSERT_EQ(l.Get(1), 30);
}

// remove
TEST(List, RemoveElement) {
  // remove from middle
  ListDoublyLinked<int> l;
  l.Insert(11, 0);
  l.Insert(22, 0);
  l.Insert(33, 0);  // 33, 22, 11

  l.Remove(1);  // 22

  ASSERT_EQ(l.Size(), 2);
  ASSERT_EQ(l.Get(0), 33);
  ASSERT_EQ(l.Get(1), 11);

  // remove the head
  l.Insert(22, 1);  // 33, 22, 11
  l.Remove(0);      // 33

  ASSERT_EQ(l.Size(), 2);
  ASSERT_EQ(l.Get(0), 22);
  ASSERT_EQ(l.Get(1), 11);

  // remove the tail
  l.Insert(33, 0);  // 33, 22, 11
  l.Remove(2);      // 11

  ASSERT_EQ(l.Size(), 2);
  ASSERT_EQ(l.Get(0), 33);
  ASSERT_EQ(l.Get(1), 22);
}

// find
TEST(List, FindElement) {
  ListDoublyLinked<int> l;
  l.Insert(11, 0);
  l.Insert(22, 0);
  l.Insert(33, 0);  // 33, 22, 11

  ASSERT_EQ(l.Size(), 3);
  ASSERT_EQ(l.Find(33), 0);
  ASSERT_EQ(l.Find(22), 1);
  ASSERT_EQ(l.Find(11), 2);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
