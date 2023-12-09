import numpy as np


def load_path_and_map(file_path):
    with open(file_path, "rt") as infile:
        lines = infile.readlines()
        path = lines[0]
        lines.pop(0)
        lines.pop(0)

        map = dict()
        for line in lines:
            components = line.strip('\n').split(" = ")
            key = components[0]
            values = components[1].strip('(').strip(')').split(', ')
            # print(f'{key} - > {values[0]}  {values[1]}')
            map[key] = values

    return path, map


def all_end_with_letter(item_list, letter):
    for item in item_list:
        if item[-1] != letter:
            return False
    return True


if __name__ == '__main__':
    path, map = load_path_and_map("input.txt")

    ind_path = list()
    for instruction in path:
        if instruction == 'L':
            ind_path.append(0)
        elif instruction == 'R':
            ind_path.append(1)

    current_key = 'AAA'
    travel_count = 0

    while current_key != 'ZZZ':
        instruction_ind = travel_count % len(ind_path)
        next_key = map[current_key][ind_path[instruction_ind]]
        current_key = next_key
        travel_count += 1
    print(f'Part 1: {travel_count}')

    current_keys = list()

    for key, _ in map.items():
        if key[-1] == 'A':
            current_keys.append(key)

    path_taken = list()
    for key in current_keys:
        key_count = 0
        while key[-1] != 'Z':
            instruction_ind = key_count % len(ind_path)
            next_key = map[key][ind_path[instruction_ind]]
            key = next_key
            key_count += 1
        path_taken.append(key_count)
    print(f'Part 2: {np.lcm.reduce(path_taken)}')
