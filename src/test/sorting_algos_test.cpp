#include "sorting_algos.hpp"

#include <numeric>
#include <random>
#include <vector>

#include "gtest/gtest.h"

class SortingAlgosTest : public testing::Test {
 protected:
  auto static constexpr size = 1024;
  std::vector<int> reference_vector{};
  std::vector<int> scrambled_vector{};

  SortingAlgosTest() : reference_vector(size) {
    std::iota(reference_vector.begin(), reference_vector.end(), 0);
    scrambled_vector = reference_vector;
    auto g = std::mt19937(0);
    std::shuffle(scrambled_vector.begin(), scrambled_vector.end(), g);
  }
};

TEST_F(SortingAlgosTest, InsertionSortTest) {
  insertion_sort(scrambled_vector.begin(), scrambled_vector.end());

  for (std::size_t i = 0; i < reference_vector.size(); ++i) {
    EXPECT_EQ(reference_vector[i], scrambled_vector[i]);
  }
}

TEST_F(SortingAlgosTest, InsertionSort2Test) {
  insertion_sort_2(scrambled_vector.begin(), scrambled_vector.end());

  for (std::size_t i = 0; i < reference_vector.size(); ++i) {
    EXPECT_EQ(reference_vector[i], scrambled_vector[i]);
  }
}

TEST_F(SortingAlgosTest, BubbleSortTest) {
  bubble_sort(scrambled_vector.begin(), scrambled_vector.end());

  for (std::size_t i = 0; i < reference_vector.size(); ++i) {
    EXPECT_EQ(reference_vector[i], scrambled_vector[i]);
  }
}

TEST_F(SortingAlgosTest, QuickSortTest) {
  quick_sort(scrambled_vector.begin(), scrambled_vector.end());

  for (std::size_t i = 0; i < reference_vector.size(); ++i) {
    EXPECT_EQ(reference_vector[i], scrambled_vector[i]);
  }
}

TEST_F(SortingAlgosTest, HeapSortTest) {
  heap_sort(scrambled_vector.begin(), scrambled_vector.end());

  for (std::size_t i = 0; i < reference_vector.size(); ++i) {
    EXPECT_EQ(reference_vector[i], scrambled_vector[i]);
  }
}
