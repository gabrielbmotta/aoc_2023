input = open("input.txt", "r").readlines()

input = [line.split() for line in input]

cards = ['2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' ]
charMap = {'2': '2', '3': '3', '4': '4', '5': '5', '6': '6', '7': '7', '8': '8', '9': '9', 'T': 'A', 'J': 'B', 'Q': 'C', 'K': 'D', 'A': 'E'}


def score(handtuple):
    hand = handtuple[0]
    if len(set(hand)) == 1: # 5 of a kind
        score = '6'
    elif len(set(hand)) == 2: # 4 of a kind or full house
        if hand.count(hand[0]) in [1,4]: # 4 of a kind
            score = '5'
        else: # full house
            score = '4'
    elif len(set(hand)) == 3: # 3 of a kind or 2 pair
        # if 3 of a kind
        if (hand.count(hand[0]) == 3 or
            hand.count(hand[1]) == 3 or
            hand.count(hand[2]) == 3):
            score = '3'
        else:
            score = '2'
    elif len(set(hand)) == 4: # 1 pair
        score = '1'
    else: # high card
        score = '0'

    for idx, card in enumerate(hand):
        score += charMap[card]

    return score

inputTuples = []
for hand, bid in input:
    inputTuples.append((hand, bid))
inputTuples = sorted(inputTuples, key=score)

total = 0
for idx, tuple in enumerate(inputTuples):
    rank = idx + 1
    total += int(tuple[1]) * rank
print(total)
