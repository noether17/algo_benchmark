include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(sorting_algos_benchmark sorting_algos_benchmark.cpp)
target_link_libraries(sorting_algos_benchmark
  sorting_algos
  benchmark::benchmark
  benchmark::benchmark_main
)
