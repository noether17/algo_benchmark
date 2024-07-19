#include "sorting_algos.hpp"

#include <vector>

#include "gtest/gtest.h"

TEST(SortingAlgosTest, InsertionSortTest) {
  auto v = std::vector{5, 2, 4, 6, 1, 3};

  insertion_sort(v.begin(), v.end());

  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(4, v[3]);
  EXPECT_EQ(5, v[4]);
  EXPECT_EQ(6, v[5]);
}

TEST(SortingAlgosTest, BubbleSortTest) {
  auto v = std::vector{5, 2, 4, 6, 1, 3};

  bubble_sort(v.begin(), v.end());

  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(4, v[3]);
  EXPECT_EQ(5, v[4]);
  EXPECT_EQ(6, v[5]);
}

TEST(SortingAlgosTest, QuickSortTest) {
  auto v = std::vector{5, 2, 4, 6, 1, 3};

  quick_sort(v.begin(), v.end());

  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(4, v[3]);
  EXPECT_EQ(5, v[4]);
  EXPECT_EQ(6, v[5]);
}

TEST(SortingAlgosTest, HeapSortTest) {
  auto v = std::vector{5, 2, 4, 6, 1, 3};

  heap_sort(v.begin(), v.end());

  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(4, v[3]);
  EXPECT_EQ(5, v[4]);
  EXPECT_EQ(6, v[5]);
}
