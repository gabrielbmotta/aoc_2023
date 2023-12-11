def build_sequence_tree(sequence):
    seq_tree = [sequence]
    while not all(x == 0 for x in seq_tree[-1]):
        new_layer = list()
        for i, element in enumerate(seq_tree[-1]):
            if i + 1 == len(seq_tree[-1]):
                seq_tree.append(new_layer)
                break
            new_layer.append(seq_tree[-1][i + 1] - seq_tree[-1][i])
    return seq_tree


def extrapolate_right(tree):
    for ind in reversed(range(len(tree) - 1)):
        tree[ind].append(tree[ind][-1] + tree[ind + 1][-1])


def extrapolate_left(tree):
    for ind in reversed(range(len(tree) - 1)):
        tree[ind].insert(0, tree[ind][0] - tree[ind + 1][0])


file_path = "input.txt"
rolling_sum_pt1 = 0
rolling_sum_pt2 = 0
with open(file_path, "rt") as infile:
    input = infile.readlines()
    for line in input:
        sequence = [int(num) for num in line.strip('\n').split()]
        tree = build_sequence_tree(sequence)
        extrapolate_right(tree)
        extrapolate_left(tree)
        rolling_sum_pt1 += tree[0][-1]
        rolling_sum_pt2 += tree[0][0]
    print(f'Part 1: {rolling_sum_pt1}')
    print(f'Part 2: {rolling_sum_pt2}')
