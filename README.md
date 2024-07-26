# Building

This repository uses Google Test and Google Benchmark. If these are installed, the project can be built using

```
mkdir build
cd build
cmake ..
cmake --build .
```

# Plotting

To plot benchmark results, first perform the above build commands and then run the following command in the build directory:

```
cmake --build . --target plot_benchmark
```

This will run the benchmark as well as a Python script for plotting the results. The plots will be saved in build/src/benchmark/.
