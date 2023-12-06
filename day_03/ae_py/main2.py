from helper2 import getAdjacents

with open("input.txt", "r") as f:
    input = f.readlines()

# Get all gears in input
sum = 0
for rowIdx, line in enumerate(input):
    for colIdx, char in enumerate(line):
        if char == "*":
            adjs = getAdjacents(input, rowIdx, colIdx)
            if len(adjs) == 2:
                sum += int(adjs[0]) * int(adjs[1])