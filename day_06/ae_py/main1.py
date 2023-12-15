import numpy as np

input = open("input.txt", "r").readlines()

times = [int(x) for x in input[0].split(":")[1].strip().split()]
distances = [int(x) for x in input[1].split(":")[1].strip().split()]

games = list(zip(times, distances))

ways = []
w = 0
for game in games:
    for holdTime in range(0, game[0] + 1):
        if holdTime * (game[0] - holdTime) > game[1]:
            w += 1
    ways.append(w)
    w = 0
print(np.prod(ways))
