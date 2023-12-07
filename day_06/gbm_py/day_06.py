from math import prod, sqrt, floor, ceil

# def num_winnable(time, dist):
#     winnable = 0
#     for held_time in range(0, time + 1):
#         if (time - held_time) * held_time > dist:
#             winnable += 1
#     return winnable
#


def num_winnable(time, dist):
    d = (time**2) - (4 * -1 * -dist)
    x1 = (-time + sqrt(d)) / -2
    x2 = (-time - sqrt(d)) / -2
    return ceil(x2) - floor(x1) - 1


with open("input.txt", "rt") as infile:
    times = [int(t) for t in infile.readline().split(':')[1].split()]
    dists = [int(d) for d in infile.readline().split(':')[1].split()]

winnables = list()
for t, d in zip(times, dists):
    winnables.append(num_winnable(t, d))

print(f'Part 1: {prod(winnables)}')

time = int("".join([str(t) for t in times]))
dist = int("".join([str(d) for d in dists]))

print(f'Part 2: {num_winnable(time,dist)}')
