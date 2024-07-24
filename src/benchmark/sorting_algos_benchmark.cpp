#include <benchmark/benchmark.h>

#include <algorithm>
#include <random>
#include <vector>

#include "sorting_algos.hpp"

#define REPEAT2(X) X X
#define REPEAT4(X) REPEAT2(REPEAT2(X))
#define REPEAT16(X) REPEAT4(REPEAT4(X))
#define REPEAT(X) REPEAT16(REPEAT16(X))

auto constexpr n_repetitions = 256;

auto constexpr min_array_size = 1 << 0;
auto constexpr max_array_size = 1 << 10;

struct NoSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    no_sort(first, last);
  }
};

struct InsertionSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    insertion_sort(first, last);
  }
};

struct BinaryInsertionSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    binary_insertion_sort(first, last);
  }
};

struct BubbleSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    bubble_sort(first, last);
  }
};

struct QuickSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    quick_sort(first, last);
  }
};

struct HeapSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    heap_sort(first, last);
  }
};

template <typename SortType>
static void BM_Sort(benchmark::State& state) {
  auto const size = state.range(0);

  auto const total_items = size * n_repetitions;
  auto const reference_vector = [total_items]() {
    auto v = std::vector<int>(total_items);
    std::iota(v.begin(), v.end(), 0);
    auto gen = std::mt19937(0);
    std::shuffle(v.begin(), v.end(), gen);
    return v;
  }();

  auto vector_copy = std::vector<int>(total_items);
  for (auto _ : state) {
    std::copy(reference_vector.begin(), reference_vector.end(),
              vector_copy.begin());
    auto data = vector_copy.data();
    auto current_begin = vector_copy.begin();
    auto current_end = current_begin + size;
    REPEAT(SortType::sort(current_begin, current_end);
           benchmark::DoNotOptimize(data);
           benchmark::DoNotOptimize(current_begin += size);
           benchmark::DoNotOptimize(current_end += size);
           benchmark::ClobberMemory();)
    // faster to increment current_begin and current_end separately than to
    // assign current_begin = current_end
  }

  state.SetItemsProcessed(state.iterations() * total_items);
}

BENCHMARK_TEMPLATE(BM_Sort, NoSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, InsertionSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, BinaryInsertionSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, BubbleSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, QuickSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, HeapSorter)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
