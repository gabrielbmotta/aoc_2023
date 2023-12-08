def loadPathAndMap(file_path):
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


path, map = loadPathAndMap("input.txt")

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

print(travel_count)
