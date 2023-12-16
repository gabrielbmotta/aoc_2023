import numpy as np

input = open("input.txt", "r").readlines()

time = int("".join(input[0].split(":")[1].strip().split()))
distance = int("".join(input[1].split(":")[1].strip().split()))

for holdTime in range(0,time+1):
    if holdTime * (time - holdTime) > distance:
        firstWin = holdTime
        break
for holdTime in reversed(range(0, time + 1)):
    if holdTime * (time - holdTime) > distance:
        lastWin = holdTime
        break

print(len(range(firstWin, lastWin + 1)))
