#pragma once

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

// quick sort

// heapsort
