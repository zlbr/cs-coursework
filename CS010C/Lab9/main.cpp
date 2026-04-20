#include <gtest/gtest.h>

#include "cuckoo_hashing.h"

TEST(CuckooHashing, EmptyTableContainsNothing) {
  CuckooHashing<int> ht;
  EXPECT_FALSE(ht.Contains(42));
}

TEST(CuckooHashing, InsertAndContains) {
  CuckooHashing<int> ht;
  ht.Insert(10);
  EXPECT_TRUE(ht.Contains(10));
  EXPECT_FALSE(ht.Contains(20));

  ht.Insert(20);
  ht.Insert(30);
  EXPECT_TRUE(ht.Contains(10));
  EXPECT_TRUE(ht.Contains(20));
  EXPECT_TRUE(ht.Contains(30));
}

TEST(CuckooHashing, DuplicateInsert) {
  CuckooHashing<int> ht;
  ht.Insert(5);
  ht.Insert(5);
  EXPECT_TRUE(ht.Contains(5));
}

TEST(CuckooHashing, Remove) {
  CuckooHashing<int> ht;
  ht.Insert(10);
  ht.Insert(20);
  ht.Insert(30);

  ht.Remove(20);
  EXPECT_FALSE(ht.Contains(20));
  EXPECT_TRUE(ht.Contains(10));
  EXPECT_TRUE(ht.Contains(30));
}

TEST(CuckooHashing, RemoveNonExistent) {
  CuckooHashing<int> ht;
  ht.Insert(10);
  ht.Remove(99);
  EXPECT_FALSE(ht.Contains(99));
  EXPECT_TRUE(ht.Contains(10));
}

TEST(CuckooHashing, RemoveAll) {
  CuckooHashing<int> ht;
  ht.Insert(1);
  ht.Insert(2);
  ht.Insert(3);
  ht.Remove(1);
  ht.Remove(2);
  ht.Remove(3);
  EXPECT_FALSE(ht.Contains(1));
  EXPECT_FALSE(ht.Contains(2));
  EXPECT_FALSE(ht.Contains(3));
}

TEST(CuckooHashing, ReinsertAfterRemove) {
  CuckooHashing<int> ht;
  ht.Insert(42);
  ht.Remove(42);
  EXPECT_FALSE(ht.Contains(42));

  ht.Insert(42);
  EXPECT_TRUE(ht.Contains(42));
}

TEST(CuckooHashing, BulkInsertStressResize) {
  CuckooHashing<int> ht;
  const int N = 50;
  for (int i = 0; i < N; ++i) {
    ht.Insert(i * 7);
  }
  for (int i = 0; i < N; ++i) {
    EXPECT_TRUE(ht.Contains(i * 7)) << "missing key: " << i * 7;
  }
}

TEST(CuckooHashing, CollisionProneKeys) {
  CuckooHashing<int> ht;
  ht.Insert(0);
  ht.Insert(11);
  ht.Insert(22);
  ht.Insert(33);
  ht.Insert(44);

  EXPECT_TRUE(ht.Contains(0));
  EXPECT_TRUE(ht.Contains(11));
  EXPECT_TRUE(ht.Contains(22));
  EXPECT_TRUE(ht.Contains(33));
  EXPECT_TRUE(ht.Contains(44));
}

TEST(CuckooHashing, PrintTableDoesNotCrash) {
  CuckooHashing<int> ht;
  ht.Insert(10);
  ht.Insert(20);
  ht.Insert(30);
  EXPECT_NO_FATAL_FAILURE(ht.PrintTable());
}
