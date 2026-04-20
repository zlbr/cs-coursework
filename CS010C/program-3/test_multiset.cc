#include <gtest/gtest.h>

#include "multiset.h"

TEST(Multiset, Empty) {
  Multiset<int> mset;

  /* Should be fully empty */
  EXPECT_EQ(mset.Empty(), true);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_THROW(mset.Count(42), std::exception);
}

TEST(Multiset, OneKey) {
  Multiset<int> mset;

  /* Test some insertion */
  mset.Insert(23);
  mset.Insert(42);
  mset.Insert(42);
  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Min(), 23);
  EXPECT_EQ(mset.Max(), 42);
  EXPECT_EQ(mset.Count(42), 2);
}

TEST(Multiset, RemoveRoot) {
  Multiset<int> mset;
  mset.Insert(10);
  mset.Insert(5);
  mset.Insert(15);
  mset.Remove(10);
  EXPECT_FALSE(mset.Contains(10));
  EXPECT_EQ(mset.Size(), 2);
  EXPECT_EQ(mset.Min(), 5);
  EXPECT_EQ(mset.Max(), 15);
}

TEST(Multiset, InsertDupes) {
  Multiset<int> mset;
  mset.Insert(10);
  mset.Insert(10);
  mset.Insert(10);
  mset.Insert(10);
  mset.Remove(10);
  mset.Remove(10);

  EXPECT_EQ(mset.Size(), 2);
  EXPECT_EQ(mset.Count(10), 2);
}

TEST(Multiset, MinMaxSingleElement) {
  Multiset<int> mset;
  mset.Insert(42);
  EXPECT_EQ(mset.Min(), 42);
  EXPECT_EQ(mset.Max(), 42);
}

TEST(Multiset, MinMax) {
  Multiset<int> mset;
  mset.Insert(1);
  mset.Insert(10);
  mset.Insert(5);
  EXPECT_EQ(mset.Min(), 1);
  EXPECT_EQ(mset.Max(), 10);
}

//
// @@@ Add more unit tests here to increase coverage @@@
//
