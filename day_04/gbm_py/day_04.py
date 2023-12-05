def get_games():
    with open("input.txt", "rt") as infile:
        games = list()
        for line in infile.readlines():
            win_nums, card_nums = line.strip('\n').split(':')[1].split('|')
            games.append((win_nums.split(), card_nums.split()))
        return games


games = get_games()

total_score_pt1 = 0
for win_nums, card_nums in games:
    score = 0
    for num in card_nums:
        if num in win_nums:
            score = score * 2 if score != 0 else 1
    total_score_pt1 += score

print(f'Part 1: {total_score_pt1}')

card_amt = [1 for game in games]
for it, game in enumerate(games):
    win_nums, card_nums = game
    score = 0
    for num in card_nums:
        if num in win_nums:
            score += 1
    for i in range(1, score + 1):
        if it + i >= len(card_amt):
            continue
        card_amt[it+i] += card_amt[it]

print(f'Part 2: {sum(card_amt)}')
