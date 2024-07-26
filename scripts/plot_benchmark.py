import json
import matplotlib.pyplot as plt
import numpy as np

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
        element_bytes = { 'Small': 4, 'Medium': 64, 'Large': 1024 }
        for element_size in unique_element_sizes:
            element_size_indices = np.where(element_sizes == element_size)
            current_family_indices = family_indices[np.where(element_sizes == element_size)]
            unique_family_indices = np.unique(current_family_indices)
            for family_index in unique_family_indices:
                current_indices = np.where(family_indices == family_index)
                algo_name = algo_names[current_indices[0][0]]
                plt.loglog(array_sizes[current_indices], seconds_per_item[current_indices], label=algo_name)
            plt.xlabel("Items in Array")
            plt.xlim(1, 1024)
            plt.ylabel("Time per Item (s)")
            plt.title(f"Performance of Sorting Algorithms with {element_bytes[element_size]}B Elements")
            plt.legend()
            plt.grid()
            plt.show()

if __name__ == "__main__":
    main()
