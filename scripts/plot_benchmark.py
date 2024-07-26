import json
import matplotlib.pyplot as plt
import numpy as np

def main():
    with open("data.json") as input_file:
        # read json file
        data = json.load(input_file)
        caches = data["context"]["caches"]
        benchmarks = data["benchmarks"]
        family_indices = np.array([int(bm["family_index"]) for bm in benchmarks])
        unique_family_indices = np.unique(family_indices)
        algo_names = np.array([str(bm["name"].split('<')[1].split('>')[0][:-2])
                               for bm in benchmarks])
        array_sizes = np.array([int(bm["name"].split('/')[-1]) for bm in benchmarks])
        items_per_second = np.array([float(bm["items_per_second"]) for bm in benchmarks])
        seconds_per_item = 1.0 / items_per_second

        for family in unique_family_indices:
            current_indices = np.where(family_indices == family)
            current_algo_name = algo_names[current_indices][0]
            plt.loglog(array_sizes[current_indices], seconds_per_item[current_indices],
                       label=current_algo_name)
        plt.xlabel("Items in Array")
        plt.ylabel("Time per Item (s)")
        plt.legend()
        plt.grid()
        plt.show()

if __name__ == "__main__":
    main()
