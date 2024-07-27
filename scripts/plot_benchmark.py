import json
import matplotlib.pyplot as plt
import numpy as np

element_bytes = { 'Small': 4, 'Medium': 64, 'Large': 1024 }
repetitions = 256
markers = {'NoSort': '', 'InsertionSort': '.', 'BinaryInsertionSort': '.',
           'BubbleSort': 'o', 'QuickSort': '+', 'HoareQuickSort': '+',
           'HeapSort': 'x', 'MergeSort': '^', 'SBOMergeSort': '^', 'StdSort': '*'}

def main():
    with open("data.json") as input_file:
        # read json file
        data = json.load(input_file)
        caches = data["context"]["caches"]
        benchmarks = data["benchmarks"]

        # parse data
        family_indices = np.array([int(bm["family_index"]) for bm in benchmarks])
        element_sizes = np.array([str(bm["name"].split(' ')[1].split('E')[0])
                                  for bm in benchmarks])
        algo_names = np.array([str(bm["name"].split('<')[1].split(',')[0][:-2])
                               for bm in benchmarks])
        array_sizes = np.array([int(bm["name"].split('/')[-1]) for bm in benchmarks])
        items_per_second = np.array([float(bm["items_per_second"]) for bm in benchmarks])
        seconds_per_item = 1.0 / items_per_second

        unique_element_sizes = ['Small', 'Medium', 'Large']
        for element_size in unique_element_sizes:
            plt.figure(figsize=(12,9))
            # plot data
            element_size_indices = np.where(element_sizes == element_size)
            current_family_indices = family_indices[np.where(element_sizes == element_size)]
            unique_family_indices = np.unique(current_family_indices)
            for family_index in unique_family_indices:
                current_indices = np.where(family_indices == family_index)
                algo_name = algo_names[current_indices[0][0]]
                plt.loglog(array_sizes[current_indices], seconds_per_item[current_indices],
                           label=algo_name, marker=markers[algo_name])

            # plot caches
            current_element_bytes = element_bytes[element_size]
            bytes_processed_per_array_item = current_element_bytes * repetitions

            l1_cache = [cache for cache in caches if cache['level'] == 1 and cache['type'] == "Data"][0]
            items_to_fill_l1 = l1_cache['size'] / bytes_processed_per_array_item
            plt.axvline(items_to_fill_l1, color='b', alpha=0.5, linestyle='--', label="Caches")

            l2_cache = [cache for cache in caches if cache['level'] == 2][0]
            items_to_fill_l2 = l2_cache['size'] / bytes_processed_per_array_item
            plt.axvline(items_to_fill_l2, color='b', alpha=0.5, linestyle='--')

            l3_cache = [cache for cache in caches if cache['level'] == 3][0]
            items_to_fill_l3 = l3_cache['size'] / bytes_processed_per_array_item
            plt.axvline(items_to_fill_l3, color='b', alpha=0.5, linestyle='--')

            plt.xlabel("Items in Array")
            plt.xlim(1, 1024)
            plt.ylabel("Time per Item (s)")
            plt.title(f"Performance of Sorting Algorithms with {current_element_bytes}B Elements")
            plt.legend(loc='upper left')
            plt.grid()
            plt.savefig(f"sorting_alg_perf_at_{current_element_bytes}_bytes.png")

if __name__ == "__main__":
    main()
