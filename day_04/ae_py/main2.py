with open("input.txt", "r") as f:
    input = f.readlines()
cardCount = [1 for line in input]
for idx, line in enumerate(input):
    nums = line.split(":")[1]
    myNums = nums.split("|")[0].replace("  ", " ").strip().split(" ")
    winningNums = nums.split("|")[1].replace("  ", " ").strip().split(" ")
    wins = len(set(myNums).intersection(winningNums))
    for cardIdx in range(idx + 1, idx + wins + 1):
        cardCount[cardIdx] += cardCount[idx]
    print(f"Card {idx+1} wins {cardCount[idx]} copies of {wins} cards. cardCount: \n{cardCount}")
print(sum(cardCount))
