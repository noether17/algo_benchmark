#pragma once

#include <algorithm>
#include <array>
#include <vector>

// no sort
template <typename RandomIt>
void no_sort(RandomIt, RandomIt) {}

// insertion sort
template <typename RandomIt>
void insertion_sort(RandomIt first, RandomIt last) {
  for (auto next = first + 1; next < last; ++next) {
    auto insert_value = *next;
    auto insert_pos = next;
    for (; insert_pos > first and insert_value < *(insert_pos - 1);
         --insert_pos) {
      *insert_pos = *(insert_pos - 1);
    }
    *insert_pos = insert_value;
  }
}

// binary insertion sort
template <typename RandomIt>
void binary_insertion_sort(RandomIt first, RandomIt last) {
  for (auto next = first + 1; next < last; ++next) {
    std::rotate(std::upper_bound(first, next, *next), next, next + 1);
  }
}

// bubble sort
template <typename RandomIt>
void bubble_sort(RandomIt first, RandomIt last) {
  auto swapped = true;
  while (swapped) {
    swapped = false;
    for (auto bubble = first; bubble < last - 1; ++bubble) {
      if (*(bubble + 1) < *bubble) {
        std::swap(*(bubble + 1), *bubble);
        swapped = true;
      }
    }
    --last;
  };
}

// quick sort
template <typename RandomIt>
void quick_sort(RandomIt first, RandomIt last) {
  if ((last - first) < 2) {
    return;
  }
  auto pivot_loc = first + (last - first) / 2;  // use midpoint as pivot
  auto const pivot = *pivot_loc;
  std::swap(*pivot_loc, *(last - 1));

  pivot_loc = first;
  for (auto current = first; current != last - 1; ++current) {
    if (*current < pivot) {
      std::swap(*pivot_loc, *current);
      ++pivot_loc;
    }
  }
  std::swap(*pivot_loc, *(last - 1));

  quick_sort(first, pivot_loc);
  quick_sort(pivot_loc + 1, last);
}

// quick sort using Hoare partition
template <typename RandomIt>
void hoare_quick_sort(RandomIt first, RandomIt last) {
  if ((last - first) < 2) {
    return;
  }
  auto pivot_loc = first + (last - first) / 2;  // use midpoint as pivot
  auto const pivot = *pivot_loc;
  std::swap(*pivot_loc, *first);

  auto lo = first - 1;
  auto hi = last;
  while (true) {
    do {
      ++lo;
    } while (*lo < pivot);
    do {
      --hi;
    } while (pivot < *hi);
    if (not(lo < hi)) {
      break;
    }
    std::swap(*lo, *hi);
  }

  auto partition = hi + 1;
  hoare_quick_sort(first, partition);
  hoare_quick_sort(partition, last);
}

// heapsort
auto inline heap_parent(int i) { return (i - 1) / 2; }
auto inline heap_left(int i) { return 2 * i + 1; }
auto inline heap_right(int i) { return 2 * (i + 1); }

template <typename RandomIt>
void max_heap_combine(RandomIt heap_first, int heap_size, int index) {
  auto left = heap_left(index);
  if (left >= heap_size) {
    return;
  }
  auto largest = heap_first[index] < heap_first[left] ? left : index;
  auto right = heap_right(index);
  if (right < heap_size) {
    largest = heap_first[largest] < heap_first[right] ? right : largest;
  }
  if (largest != index) {
    std::swap(heap_first[index], heap_first[largest]);
    max_heap_combine(heap_first, heap_size, largest);
  }
}
template <typename RandomIt>
void heap_sort(RandomIt first, RandomIt last) {
  auto size = static_cast<int>(last - first);
  auto last_parent = size / 2 - 1;
  for (auto i = last_parent; i >= 0; --i) {
    max_heap_combine(first, size, i);
  }
  for (--last; last != first; --last) {
    std::swap(*first, *last);
    max_heap_combine(first, last - first, 0);
  }
}

// merge sort
template <typename RandomIt>
void merge(RandomIt first, RandomIt midpoint, RandomIt last) {
  auto left_size = midpoint - first;
  auto left_copy = std::vector<typename RandomIt::value_type>{};
  left_copy.reserve(left_size);
  left_copy.insert(left_copy.end(), first, midpoint);

  auto insert_point = first;
  auto left_front = left_copy.begin();
  auto right_front = midpoint;
  while (left_front != left_copy.end() and right_front != last) {
    if (*right_front < *left_front) {
      *insert_point++ = *right_front++;
    } else {
      *insert_point++ = *left_front++;
    }
  }
  std::copy(left_front, left_copy.end(), insert_point);
}
template <typename RandomIt>
void merge_sort(RandomIt first, RandomIt last) {
  if ((last - first) < 2) {
    return;
  }

  auto midpoint = first + (last - first) / 2;
  merge_sort(first, midpoint);
  merge_sort(midpoint, last);
  merge(first, midpoint, last);
}

// merge sort with small buffer optimization
template <typename RandomIt>
void sbo_merge(RandomIt first, RandomIt midpoint, RandomIt last) {
  using Value = typename RandomIt::value_type;
  auto static constexpr buffer_size = 8;

  auto left_size = midpoint - first;
  auto left_buffer = std::array<Value, buffer_size>{};
  auto left_vec = std::vector<Value>{};
  auto *left_first =
      left_size <= buffer_size
          ? (std::copy(first, midpoint, left_buffer.begin()),
             left_buffer.data())
          : (left_vec.reserve(left_size),
             left_vec.insert(left_vec.end(), first, midpoint), left_vec.data());
  auto *left_last = left_first + left_size;

  auto insert_point = first;
  auto right_first = midpoint;
  while (left_first != left_last and right_first != last) {
    if (*right_first < *left_first) {
      *insert_point++ = *right_first++;
    } else {
      *insert_point++ = *left_first++;
    }
  }
  std::copy(left_first, left_last, insert_point);
}
template <typename RandomIt>
void sbo_merge_sort(RandomIt first, RandomIt last) {
  if ((last - first) < 2) {
    return;
  }

  auto midpoint = first + (last - first) / 2;
  merge_sort(first, midpoint);
  merge_sort(midpoint, last);
  sbo_merge(first, midpoint, last);
}
