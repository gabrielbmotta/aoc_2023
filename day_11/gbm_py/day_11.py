import numpy as np


def load_map(file):
    with open(file, "rt") as infile:
        input = infile.readlines()
        return np.array([list(line.strip('\n')) for line in input])


def get_galaxy_coords(galaxy_map):
    galaxies = list()
    for i, row in enumerate(galaxy_map):
        for j, v in enumerate(row):
            if v == "#":
                galaxies.append((i, j))
    return galaxies


def expand_galaxy(galaxy_map, coords, exp_amount):
    empty_row_indices = list()
    for i, row in enumerate(galaxy_map):
        if np.all(row == '.'):
            empty_row_indices.append(i)

    for i in reversed(range(len(empty_row_indices))):
        coords = [(coord[0] + exp_amount, coord[1])
                  if coord[0] > empty_row_indices[i]
                  else coord for coord in coords]

    empty_col_indices = list()
    for i, col in enumerate(galaxy_map.T):
        if np.all(col == '.'):
            empty_col_indices.append(i)

    for i in reversed(range(len(empty_col_indices))):
        coords = [(coord[0], coord[1] + exp_amount)
                  if coord[1] > empty_col_indices[i]
                  else coord
                  for coord in coords]

    return coords


def path_length(path):
    return abs(path[0][0] - path[1][0]) + abs(path[0][1] - path[1][1])


def total_path_len(galaxy_coords):
    path_len = 0
    other_coords = galaxy_coords.copy()
    for i, galaxy in enumerate(galaxy_coords):
        other_coords.remove(galaxy)
        for other in other_coords:
            path_len += path_length((galaxy, other))
    return path_len


if __name__ == "__main__":
    galaxy_map = load_map("input.txt")
    galaxy_coords = get_galaxy_coords(galaxy_map)

    galaxy_coords_pt1 = expand_galaxy(galaxy_map, galaxy_coords, 1)
    galaxy_coords_pt2 = expand_galaxy(galaxy_map, galaxy_coords, 999999)

    for i, coords in enumerate([galaxy_coords_pt1, galaxy_coords_pt2]):
        print(f'Part {i + 1}: {total_path_len(coords)}')
