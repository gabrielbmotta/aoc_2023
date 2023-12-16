from math import inf
from helper1 import mapLine, mapObj

with open("input.txt", "r") as f:
    input = f.readlines()

# Get seeds
seeds = [int(x) for x in input[0].split(":")[1].strip().split(" ")]

# Get maps
maps = []
mapLines = []
for line in input[2:]:
    if ":" in line:
        mapName = line.split(" ")[0]
    elif line[0].isnumeric():
        mapLines.append(mapLine(*[int(x) for x in line.split(" ")]))
    else:
        maps.append(mapObj(mapName, mapLines))
        mapName = ""
        mapLines = []
maps.append(mapObj(mapName, mapLines))

lowest = inf
for seed in seeds:
    current = seed
    for map in maps:
        current = map.traverse(current)
    if current < lowest:
        lowest = current
print(lowest)
