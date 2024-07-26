include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(sorting_algos_benchmark sorting_algos_benchmark.cpp)
target_link_libraries(sorting_algos_benchmark
  sorting_algos
  benchmark::benchmark
  benchmark::benchmark_main
)

add_custom_target(plot_benchmark
  COMMAND sorting_algos_benchmark --benchmark_out=data.json
  COMMAND python ${CMAKE_SOURCE_DIR}/scripts/plot_benchmark.py
)
add_dependencies(plot_benchmark sorting_algos_benchmark)
