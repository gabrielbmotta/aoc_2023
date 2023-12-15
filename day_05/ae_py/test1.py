from helper1 import mapLine, mapObj

with open("testInput.txt", "r") as f:
    input = f.readlines()

# Get seeds
seeds = [int(x) for x in input[0].split(":")[1].strip().split(" ")]

# Get maps
maps = []
mapLines = []
for line in input[2:]:
    if ":" in line:
        mapName = line.split(" ")[0].split("-")[2]
    elif line[0].isnumeric():
        mapLines.append(mapLine(*[int(x) for x in line.split(" ")]))
    else:
        maps.append(mapObj(mapName, mapLines))
        mapName = ""
        mapLines = []
maps.append(mapObj(mapName, mapLines))

for seed in seeds:
    current = seed
    out = f"seed: {seed}"
    for map in maps:
        current = map.traverse(current)
        out += f", {map.name}: {current}"
    out += "."
    print(out)
