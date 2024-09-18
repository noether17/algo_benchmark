#include <benchmark/benchmark.h>

#include <algorithm>
#include <array>
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

struct HoareQuickSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    hoare_quick_sort(first, last);
  }
};

struct HeapSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    heap_sort(first, last);
  }
};

struct MergeSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    merge_sort(first, last);
  }
};

struct SBOMergeSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    sbo_merge_sort(first, last);
  }
};

struct StdSorter {
  template <typename RandomIt>
  void static sort(RandomIt first, RandomIt last) {
    std::sort(first, last);
  }
};

template <int N>
struct Element {
  std::array<int, N> data{};
  Element() = default;
  Element(int i) : data{i} {}
  friend bool operator<(Element const& a, Element const& b) {
    return a.data[0] < b.data[0];
  }
};

template <typename SortType, typename T>
static void BM_Sort(benchmark::State& state) {
  auto const size = state.range(0);

  auto const total_items = size * n_repetitions;
  auto const reference_vector = [total_items]() {
    auto v = std::vector<T>(total_items);
    std::iota(v.begin(), v.end(), 0);
    auto gen = std::mt19937(0);
    std::shuffle(v.begin(), v.end(), gen);
    return v;
  }();

  auto vector_copy = std::vector<T>(total_items);
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

using SmallElement = Element<1>;
using MediumElement = Element<16>;
using LargeElement = Element<256>;

// Perform benchmarks with SmallElement
BENCHMARK_TEMPLATE(BM_Sort, NoSorter, SmallElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, InsertionSorter, SmallElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, BinaryInsertionSorter, SmallElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, BubbleSorter, SmallElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, QuickSorter, SmallElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, HoareQuickSorter, SmallElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, HeapSorter, SmallElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, MergeSorter, SmallElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, SBOMergeSorter, SmallElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, StdSorter, SmallElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);

// Repeat with MediumElement
BENCHMARK_TEMPLATE(BM_Sort, NoSorter, MediumElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, InsertionSorter, MediumElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, BinaryInsertionSorter, MediumElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, BubbleSorter, MediumElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, QuickSorter, MediumElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, HoareQuickSorter, MediumElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, HeapSorter, MediumElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, MergeSorter, MediumElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, SBOMergeSorter, MediumElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, StdSorter, MediumElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);

// Repeat with LargeElement
BENCHMARK_TEMPLATE(BM_Sort, NoSorter, LargeElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, InsertionSorter, LargeElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, BinaryInsertionSorter, LargeElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, BubbleSorter, LargeElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, QuickSorter, LargeElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, HoareQuickSorter, LargeElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, HeapSorter, LargeElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, MergeSorter, LargeElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
// BENCHMARK_TEMPLATE(BM_Sort, SBOMergeSorter, LargeElement)
//     ->RangeMultiplier(2)
//     ->Range(min_array_size, max_array_size);
BENCHMARK_TEMPLATE(BM_Sort, StdSorter, LargeElement)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size);
