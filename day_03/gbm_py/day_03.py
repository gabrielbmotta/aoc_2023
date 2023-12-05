import numpy as np


def parse_parts_from_schematic(foccus_part=None):
    with open("input.txt", "rt") as infile:
        matrix = np.array([list(line.strip()) for line in infile.readlines()])

    dim_row, dim_col = matrix.shape

    parts = dict()

    # we intentionally do not include the first/last row/column because the
    # input has no parts there and it saves us a ton of bounds checking :)
    for i in range(1, dim_row - 1):
        for j in range(1, dim_col - 1):
            if matrix[i][j].isdigit() or matrix[i][j] == '.':
                continue
            if(foccus_part is not None and matrix[i][j] != foccus_part):
                continue
            if (i, j) not in parts:
                parts[(i, j)] = list()
            for di in range(-1, 2):
                for dj in range(-1, 2):
                    if matrix[i + di][j + dj].isdigit():
                        ind = j + dj
                        num_str = ''
                        while(ind > 0 and matrix[i+di][ind - 1].isdigit()):
                            ind -= 1
                        while(ind < dim_col and matrix[i+di][ind].isdigit()):
                            num_str = np.char.add(num_str, matrix[i+di][ind])
                            ind += 1
                        num = num_str.astype(int).item()
                        if num not in parts[(i, j)]:
                            parts[(i, j)].append(num)
    return parts


parts = parse_parts_from_schematic()
sum = 0
for _, val in parts.items():
    # print(f'{key}: {val}')
    for item in val:
        sum += item

gear_sum = 0
gears = parse_parts_from_schematic('*')
for _, val in gears.items():
    if len(val) == 2:
        gear_sum += val[0] * val[1]

print(f'Part 1: {sum}')
print(f'Part 2: {gear_sum}')
