import argparse
import subprocess

def list_of_strings(strs):
    return strs.split(',')

def list_of_ints(arg):
    return list(map(int, arg.split(',')))

events = "cycles,instructions,L1-dcache-loads,L1-dcache-load-misses," \
         + "LLC-loads,LLC-load-misses,branches,branch-misses"

benchmark = "./src/benchmark/sorting_algos_benchmark" # must be run from build dir

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--element-sizes', '-s', type=list_of_strings, help="Small,Medium,Large")
    parser.add_argument('--array-sizes', '-n', type=list_of_ints, help="Powers of 2, up to 1024")
    parser.add_argument('--algorithms', '-a', type=list_of_strings, help="NoSort,InsertionSort,"
                        + "BinaryInsertionSort,BubbleSort,QuickSort,HoareQuickSort,HeapSort,"
                        + "MergeSort,SBOMergeSort,StdSort")
    parser.add_argument('--iterations', '-i', type=int, default=1000, help="Number of iterations "
                        + "for each benchmark")
    parser.add_argument('--output-file', '-o', type=str, help="Path to output file.")

    args = parser.parse_args()
    console_output = ""
    for s in args.element_sizes:
        for n in args.array_sizes:
            for alg in args.algorithms:
                filter_str = f"<{alg}er, {s}Element>/{n}$"
                p = subprocess.run(["perf", "stat", "-e", events, benchmark,
                                    f"--benchmark_filter={filter_str}",
                                    f"--benchmark_min_time={args.iterations}x"],
                                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                console_output += p.stdout.decode()
    if args.output_file is None:
        print(console_output)
    else:
        with open(args.output_file, 'w') as output_file:
            print(console_output, file=output_file)

if __name__ == "__main__":
    main()
