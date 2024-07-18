include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(sorting_algos_test sorting_algos_test.cpp)
target_link_libraries(sorting_algos_test
  GTest::GTest
  GTest::Main
  sorting_algos
)
add_test(NAME sorting_algos_test COMMAND sorting_algos_test)
