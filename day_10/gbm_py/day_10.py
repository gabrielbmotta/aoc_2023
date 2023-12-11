import numpy as np

dir_dict = {'|': ['N', 'S'], '-': ['W', 'E'],
            '7': ['W', 'S'], 'J': ['W', 'N'],
            'L': ['N', 'E'], 'F': ['E', 'S']}

dir_to_coord = {'N': (-1, 0), 'S': (1, 0), 'E': (0, 1), 'W': (0, -1)}


def load_map(file):
    with open(file, "rt") as infile:
        input = infile.readlines()
        return np.array([list(line.strip('\n')) for line in input])


def find_start(map):
    for i in range(len(map)):
        for j in range(len(map[i])):
            if map[i][j] == "S":
                return i, j


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
start = find_start(path_map)
print(f'{start[0]}, {start[1]}')
path_points = list()
path_points.append(start)
potential_connections = list()

if path_map[start[0] - 1][start[1]] in ('|', 'F', '7'):
    potential_connections.append((start[0] - 1, start[1]))

if path_map[start[0] + 1][start[1]] in ('|', 'J', 'L'):
    potential_connections.append((start[0] + 1, start[1]))

if path_map[start[0]][start[1] - 1] in ('-', 'L', 'F'):
    potential_connections.append((start[0], start[1] - 1))

if path_map[start[0]][start[1] + 1] in ('-', 'J', '7'):
    potential_connections.append((start[0], start[1] + 1))

print(potential_connections)

path_points.insert(0, potential_connections[0])
path_points.append(potential_connections[-1])

while find_new_adj(path_map, path_points):
    continue

print(f'Part 1: {len(path_points) / 2}')
