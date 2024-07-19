#pragma once

// no sort
template <typename RandomIt>
void no_sort(RandomIt, RandomIt) {}

// insertion sort
template <typename RandomIt>
void insertion_sort(RandomIt first, RandomIt last) {
  auto next = first + 1;
  while (next != last) {
    auto insertion_point = first;
    auto insert_value = *next;
    while (*insertion_point < insert_value) {
      ++insertion_point;
    }
    while (insertion_point != next) {
      auto temp = *insertion_point;
      *insertion_point = insert_value;
      insert_value = temp;
      ++insertion_point;
    }
    *next = insert_value;
    ++next;
  }
}

// bubble sort
template <typename RandomIt>
void bubble_sort(RandomIt first, RandomIt last) {
  while (first != last) {
    auto bubble = first;
    while (bubble != last - 1) {
      if (*(bubble + 1) < *bubble) {
        auto temp = *bubble;
        *bubble = *(bubble + 1);
        *(bubble + 1) = temp;
      }
      ++bubble;
    }
    --last;
  }
}

// quick sort
template <typename RandomIt>
void quick_sort(RandomIt first, RandomIt last) {
  if (first == last) {
    return;
  }
  auto pivot_loc = first + (last - first) / 2;  // iterator to midpoint
  auto const pivot = *pivot_loc;

  // move pivot to start
  *pivot_loc = *first;
  *first = pivot;
  pivot_loc = first;

  auto current = pivot_loc + 1;
  while (current != last) {
    if (*current < pivot) {
      *pivot_loc = *current;
      *current = *(pivot_loc + 1);
      *(pivot_loc + 1) = pivot;
      ++pivot_loc;
    }
    ++current;
  }
  quick_sort(first, pivot_loc);
  quick_sort(pivot_loc + 1, last);
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
    auto temp = heap_first[index];
    heap_first[index] = heap_first[largest];
    heap_first[largest] = temp;
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
    auto temp = *first;
    *first = *last;
    *last = temp;
    max_heap_combine(first, last - first, 0);
  }
}
