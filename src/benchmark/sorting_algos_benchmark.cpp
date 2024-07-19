#include <benchmark/benchmark.h>

#include <algorithm>
#include <random>
#include <vector>

#include "sorting_algos.hpp"

// #define REPEAT2(X) X X
// #define REPEAT4(X) REPEAT2(X) REPEAT2(X)
// #define REPEAT8(X) REPEAT4(X) REPEAT4(X)
// #define REPEAT16(X) REPEAT8(X) REPEAT8(X)
// #define REPEAT(X) REPEAT16(X) REPEAT16(X)

auto constexpr n_repetitions = 1024;
auto constexpr min_array_size = 1 << 0;
auto constexpr max_array_size = 1 << 10;
auto constexpr total_items = n_repetitions * max_array_size;

static void BM_NoSort(benchmark::State& state) {
  auto size = state.range(0);
  auto rd = std::random_device{};
  auto gen = std::mt19937(rd());
  gen.seed(1);
  auto dis = std::uniform_int_distribution<int>(0, size);

  auto v = std::vector<int>(total_items);
  std::generate(v.begin(), v.end(), [&]() { return dis(gen); });

  for (auto _ : state) {
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    for (auto iter = v.begin(); iter != v.end(); iter += size) {
      no_sort(iter, iter + size);
    }
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(total_items);
}
BENCHMARK(BM_NoSort)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);

static void BM_InsertionSort(benchmark::State& state) {
  auto size = state.range(0);
  auto rd = std::random_device{};
  auto gen = std::mt19937(rd());
  gen.seed(1);
  auto dis = std::uniform_int_distribution<int>(0, size);

  auto v = std::vector<int>(total_items);
  std::generate(v.begin(), v.end(), [&]() { return dis(gen); });

  for (auto _ : state) {
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    for (auto iter = v.begin(); iter != v.end(); iter += size) {
      insertion_sort(iter, iter + size);
    }
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(total_items);
}
BENCHMARK(BM_InsertionSort)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);

static void BM_BubbleSort(benchmark::State& state) {
  auto size = state.range(0);
  auto rd = std::random_device{};
  auto gen = std::mt19937(rd());
  gen.seed(1);
  auto dis = std::uniform_int_distribution<int>(0, size);

  auto v = std::vector<int>(total_items);
  std::generate(v.begin(), v.end(), [&]() { return dis(gen); });

  for (auto _ : state) {
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    for (auto iter = v.begin(); iter != v.end(); iter += size) {
      bubble_sort(iter, iter + size);
    }
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(total_items);
}
BENCHMARK(BM_BubbleSort)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);

static void BM_QuickSort(benchmark::State& state) {
  auto size = state.range(0);
  auto rd = std::random_device{};
  auto gen = std::mt19937(rd());
  gen.seed(1);
  auto dis = std::uniform_int_distribution<int>(0, size);

  auto v = std::vector<int>(total_items);
  std::generate(v.begin(), v.end(), [&]() { return dis(gen); });

  for (auto _ : state) {
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    for (auto iter = v.begin(); iter != v.end(); iter += size) {
      quick_sort(iter, iter + size);
    }
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(total_items);
}
BENCHMARK(BM_QuickSort)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);

static void BM_HeapSort(benchmark::State& state) {
  auto size = state.range(0);
  auto rd = std::random_device{};
  auto gen = std::mt19937(rd());
  gen.seed(1);
  auto dis = std::uniform_int_distribution<int>(0, size);

  auto v = std::vector<int>(total_items);
  std::generate(v.begin(), v.end(), [&]() { return dis(gen); });

  for (auto _ : state) {
    auto data = v.data();
    benchmark::DoNotOptimize(data);
    for (auto iter = v.begin(); iter != v.end(); iter += size) {
      heap_sort(iter, iter + size);
    }
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(total_items);
}
BENCHMARK(BM_HeapSort)
    ->RangeMultiplier(2)
    ->Range(min_array_size, max_array_size)
    ->Iterations(1);
