with open("input.txt", "r") as f:
    input = f.readlines()

points = 0
for line in input:
    nums = line.split(":")[1]
    myNums = nums.split("|")[0].replace("  ", " ").strip().split(" ")
    winningNums = nums.split("|")[1].replace("  ", " ").strip().split(" ")
    wins = len(set(myNums).intersection(winningNums))
    addedPoints = 0 if wins == 0 else 2 ** (wins - 1)
    points += addedPoints
print(points)
