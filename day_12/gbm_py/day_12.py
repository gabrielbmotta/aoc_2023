from itertools import product
from functools import cache
from multiprocessing import Process, Array

def load_map(file):
    with open(file, "rt") as infile:
        input = infile.readlines()
        lines = [line.strip('\n') for line in input]
        return [(line.split()[0],
                 tuple([int(num) for num in line.split()[1].split(',')]))
                for line in lines]


def print_map(spring_map):
    intact_count = 0
    for row in spring_map:
        print(f'{row[0]}  {row[1]} - {row[0].count("?")}')
        intact_count += 1 if '?' not in row[0] else 0


def generate_permutations(springs, key):
    blank_count = springs.count('?')
    possible_ordering = product('.#', repeat=blank_count)
    valid_count = 0
    for ord in possible_ordering:
        ord_ind = 0
        temp_str = [c for c in springs]
        normal = True
        for i, ch in enumerate(springs):
            if ch == '?':
                temp_str[i] = ord[ord_ind]
                ord_ind += 1
                if early_rej(''.join(temp_str[:i]), key):
                    normal = False
                    break
        if normal and validate_ordering(''.join(temp_str), key):
            valid_count += 1
    return valid_count


call_dict = dict()


def early_rej(springs, key):
    # print(call_dict)
    if (springs, key) in call_dict.keys():
        return call_dict[(springs, key)]
    groups = [x for x in springs.split('.') if x]
    if len(groups) > len(key):
        call_dict[(springs, key)] = True
        return True
    for group, size in zip(groups, key):
        if len(group) > size:
            call_dict[(springs, key)] = True
            return True
    call_dict[(springs, key)] = False
    return False


def validate_ordering(springs, key):
    groups = [x for x in springs.split('.') if x]
    # print(f'{groups} - {key}')
    if len(groups) != len(key):
        return False
    for group, size in zip(groups, key):
        if len(group) != size:
            return False
    return True

def expand(spring_map):
    factor = 5
    new_map = list()
    for item in spring_map:
        slist = [item[0] for _ in range(factor)]
        newstr = "?".join(slist)
        newkey = item[1] * factor
        new_map.append((newstr, newkey))
    return new_map


if __name__ == "__main__":
    spring_map = load_map("input.txt")
    # print_map(spring_map)

    # count = generate_permutations(spring_map[0][0], spring_map[0][1])
    # print(count)

    print_map(spring_map)

    counts = Array('i', [0 for _ in spring_map])

    def compute(counts, ind, springs, key):
        counts[ind] = generate_permutations(springs, key)

    proc = [Process(target=compute, args=(counts, i, tp[0], tp[1])) for i, tp in enumerate(spring_map)]

    for p in proc:
        p.start()

    for p in proc:
        p.join()

    # for i, tp in enumerate(spring_map):
    #     counts[i] = generate_permutations(tp[0], tp[1])

    print(f'Part 1: {sum(counts)}')

    # print(call_dict)

    exit(0)

    expanded = expand(spring_map)
    counts = Array('i', [0 for _ in spring_map])

    print_map(spring_map)
    print_map(expanded)

    proc = [Process(target=compute, args=(counts, i, tp[0], tp[1])) for i, tp in enumerate(expanded)]

    for p in proc:
        p.start()

    for p in proc:
        p.join()

    print(f'Part 2: {sum(counts)}')
