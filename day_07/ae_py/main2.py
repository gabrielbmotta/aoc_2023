from collections import Counter

input = open("input.txt", "r").readlines()

input = [line.split() for line in input]

cards = ['2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' ]
charMap = {'J': '1', '2': '2', '3': '3', '4': '4', '5': '5', '6': '6', '7': '7', '8': '8', '9': '9', 'T': 'A', 'Q': 'C', 'K': 'D', 'A': 'E'}


def score(handtuple):
    hand = handtuple[0]
    handNoJ = replaceJokers(hand)
    if len(set(handNoJ)) == 1:  # 5 of a kind
        score = '6'
    elif len(set(handNoJ)) == 2:  # 4 of a kind or full house
        if handNoJ.count(handNoJ[0]) in [1, 4]:  # 4 of a kind
            score = '5'
        else:  # full house
            score = '4'
    elif len(set(handNoJ)) == 3:  # 3 of a kind or 2 pair
        # if 3 of a kind
        if (handNoJ.count(handNoJ[0]) == 3 or
            handNoJ.count(handNoJ[1]) == 3 or
            handNoJ.count(handNoJ[2]) == 3):
            score = '3'
        else:
            score = '2'
    elif len(set(handNoJ)) == 4:  # 1 pair
        score = '1'
    else:  # high card
        score = '0'

    for idx, card in enumerate(hand):
        score += charMap[card]

    return score

# print(f"Test scores: hand0: {score(test0)} hand1: {score(test1)}, hand2: {score(test2)}")


def maxMode(hand):
    counter = Counter(hand.replace('J', ''))
    if counter.values():
        max_count = max(counter.values())
        modes = [k for k, v in counter.items() if v == max_count]
        highestCharVal = max([charMap[c] for c in modes])
        return list(charMap.keys())[list(charMap.values()).index(highestCharVal)]
    else:
        return 'A'

# Evidence of my sin: list(charMap.keys())[list(charMap.values()).index(max([charMap[c] for c in modes]))]


def replaceJokers(hand):
    replaceChar = maxMode(hand)
    return hand.replace('J', replaceChar)

hands = []
bids = []
inputTuples = []
for hand, bid in input:
    inputTuples.append((hand, bid))
inputTuples = sorted(inputTuples, key=score)
total = 0
for idx, tuple in enumerate(inputTuples):
    rank = idx + 1
    total += int(tuple[1]) * rank
print(total)
