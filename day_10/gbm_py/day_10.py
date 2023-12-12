import numpy as np

dir_dict = {'|': ['N', 'S'], '-': ['W', 'E'],
            '7': ['W', 'S'], 'J': ['W', 'N'],
            'L': ['N', 'E'], 'F': ['E', 'S']}

dir_to_coord = {'N': (-1, 0), 'S': (1, 0), 'E': (0, 1), 'W': (0, -1)}


def load_map(file):
    with open(file, "rt") as infile:
        input = infile.readlines()
        return np.array([list(line.strip('\n')) for line in input])


def find_start(path_map):
    for i in range(len(path_map)):
        for j in range(len(path_map[i])):
            if path_map[i][j] == "S":
                return i, j


def setup_map_path(path_map, start_point):
    path = list()
    path.append(start_point)
    potential_connections = list()
    rel_dir = list()

    if path_map[start_point[0] - 1][start_point[1]] in ('|', 'F', '7'):
        potential_connections.append((start_point[0] - 1, start_point[1]))
        rel_dir.append('N')

    if path_map[start_point[0] + 1][start_point[1]] in ('|', 'J', 'L'):
        potential_connections.append((start_point[0] + 1, start_point[1]))
        rel_dir.append('S')

    if path_map[start_point[0]][start_point[1] - 1] in ('-', 'L', 'F'):
        potential_connections.append((start_point[0], start_point[1] - 1))
        rel_dir.append('W')

    if path_map[start_point[0]][start_point[1] + 1] in ('-', 'J', '7'):
        potential_connections.append((start_point[0], start_point[1] + 1))
        rel_dir.append('E')

    for key, value in dir_dict.items():
        if set(value) == set(rel_dir):
            start_equivalent = key

    path.insert(0, potential_connections[0])
    path.append(potential_connections[-1])

    return path, start_equivalent

def find_new_adj(path_map, path_points):
    point = path_points[-1]
    point_symbol = path_map[point[0]][point[1]]
    dirs = dir_dict[point_symbol]
    possible = list()
    for dir in dirs:
        mod = dir_to_coord[dir]
        possible_point = (point[0] + mod[0], point[1] + mod[1])
        if possible_point not in path_points:
            possible.append(possible_point)

    if len(possible) != 1:
        return False

    path_points.append(possible[0])
    return True


path_map = load_map("input.txt")
start_point = find_start(path_map)
path, start_eq = setup_map_path(path_map, start_point)

while find_new_adj(path_map, path):
    continue

print(f'Part 1: {len(path) / 2}')

map[start_point[0]][start_point[1]] = start_eq

# OF-----7O
# O|IIF-7|O
# OL--JOLJO

inside_count = 0
for i, row in enumerate(path_map):
    inside = False
    for j, _ in enumerate(row):
        if (i, j) in path:
            if path_map[i][j] in ('|', 'L', 'J'):  # alternativley (| F 7)
                inside = not inside
        else:
            inside_count += 1 if inside else 0

print(f'Part 2: {inside_count}')

