from itertools import product
from functools import cache
from multiprocessing import Process, Array, Pool

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


#@cache
# def num_possible(springs, groups_key):
#     if '?' not in springs:
#         spr_groups = [x for x in springs.split('.') if x]
#         if len(spr_groups) != len(groups_key):
#             return 0
#         for group, size in zip(spr_groups, groups_key):
#             if len(group) != size:
#                 return 0
#         return 1
#
#     spr_groups = [x for x in springs.split('?')[0].split('.') if x]
#     if len(spr_groups) > len(groups_key):
#         return 0
#     for group, size in zip(spr_groups, groups_key):
#         if len(group) > size:
#             return 0
#
#     ind = springs.find('?')
#     springs_p1 = springs[:ind] + '.' + springs[ind + 1:]
#     springs_p2 = springs[:ind] + '#' + springs[ind + 1:]
#
#     return num_possible(springs_p1, groups_key) + num_possible(springs_p2, groups_key)

# @cache
# def num_possible(springs, ind, in_group, groups_key):
#     if ind == len(springs):
#         if len(groups_key) == 0 or (len(groups_key) == 1 and groups_key[0] == 0):
#             return 1
#         else:
#             return 0
#
#     if (not in_group and not groups_key) or (len(groups_key) == 1 and groups_key[0] == 0):
#         if "#" not in springs[ind:]:
#             return 1
#         else:
#             return 0
#
#     if springs[ind] == '?':
#         springs_p1 = springs[:ind] + '.' + springs[ind + 1:]
#         springs_p2 = springs[:ind] + '#' + springs[ind + 1:]
#         return num_possible(springs_p1, ind, in_group, groups_key) + num_possible(springs_p2, ind, in_group, groups_key)
#
#     if in_group:
#         if springs[ind] == '.':
#             if groups_key[0] == 0:
#                 in_group = False
#                 groups_key = groups_key[1:]
#                 return num_possible(springs, ind + 1, in_group, groups_key)
#             else:
#                 return 0
#         elif springs[ind] == '#':
#             if groups_key[0] == 0:
#                 return 0
#             else:
#                 groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
#             return num_possible(springs, ind + 1, in_group, groups_key)
#     else:
#         if springs[ind] == '.':
#             while ind + 1 < len(springs) and springs[ind + 1] == '.':
#                 ind = ind + 1
#             return num_possible(springs, ind + 1, in_group, groups_key)
#         elif springs[ind] == '#':
#             in_group = True
#             groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
#             return num_possible(springs, ind + 1, in_group, groups_key)

# @cache
# def num_possible(springs, ind, in_group, groups_key):
#     if ind == len(springs):
#         if len(groups_key) == 0 or (len(groups_key) == 1 and groups_key[0] == 0):
#             return 1
#         else:
#             return 0
#
#     if (not in_group and not groups_key) or (len(groups_key) == 1 and groups_key[0] == 0):
#         if "#" not in springs[ind:]:
#             return 1
#         else:
#             return 0
#
#     if springs[ind] == '?':
#         springs_p1 = springs[:ind] + '.' + springs[ind + 1:]
#         springs_p2 = springs[:ind] + '#' + springs[ind + 1:]
#         return num_possible(springs_p1, ind, in_group, groups_key) + num_possible(springs_p2, ind, in_group, groups_key)
#
#     if in_group:
#         if springs[ind] == '.':
#             if groups_key[0] == 0:
#                 in_group = False
#                 groups_key = groups_key[1:]
#                 return num_possible(springs, ind + 1, in_group, groups_key)
#             else:
#                 return 0
#         elif springs[ind] == '#':
#             if groups_key[0] == 0:
#                 return 0
#             groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
#
#             next_in = springs[ind:].find('.')
#             if next_in != -1 and next_in < groups_key[0]:
#                 return 0
#             while ind + 1 < len(springs) and springs[ind + 1] == '#':
#                 ind = ind + 1
#                 groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
#             return num_possible(springs, ind + 1, in_group, groups_key)
#     else:
#         if springs[ind] == '.':
#             while ind + 1 < len(springs) and springs[ind + 1] == '.':
#                 ind = ind + 1
#             return num_possible(springs, ind + 1, in_group, groups_key)
#         elif springs[ind] == '#':
#             in_group = True
#             groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
#             return num_possible(springs, ind + 1, in_group, groups_key)


# @cache
D = {}
def num_possible(springs, ind, in_group, groups_key):
    key = (ind, in_group, groups_key)
    if key in D.keys():
        return D[(ind, in_group, groups_key)]

    if ind == len(springs):
        if len(groups_key) == 0 or (len(groups_key) == 1 and groups_key[0] == 0):
            D[key] = 1
            return 1
        else:
            D[key] = 0
            return 0

    if (not in_group and not groups_key) or (len(groups_key) == 1 and groups_key[0] == 0):
        if "#" not in springs[ind:]:
            D[key] = 1
            return 1
        else:
            D[key] = 0
            return 0

    if springs[ind] == '?':
        p1 = 0
        p2 = 0
        if in_group:
            if groups_key[0] == 0:
                in_group = False
                groups_key = groups_key[1:]
                p1 = num_possible(springs, ind + 1, in_group, groups_key)
            else:
                next_in = springs[ind:].find('.')
                if next_in == -1 or next_in >= groups_key[0]:
                    while ind + 1 < len(springs) and springs[ind + 1] == '#':
                        ind = ind + 1
                        groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
                    p1 = num_possible(springs, ind + 1, in_group, groups_key)
        else:
            p2 += num_possible(springs, ind + 1, in_group, groups_key)
            groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
            p2 += num_possible(springs, ind + 1, in_group, groups_key)
        D[key] = p1 + p2
        return p1 + p2

    if in_group:
        if springs[ind] == '.':
            if groups_key[0] == 0:
                in_group = False
                groups_key = groups_key[1:]
                ans = num_possible(springs, ind + 1, in_group, groups_key)
                D[key] = ans
                return ans
            else:
                D[key] = 0
                return 0
        elif springs[ind] == '#':
            if groups_key[0] == 0:
                D[key] = 0
                return 0
            groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])

            next_in = springs[ind:].find('.')
            if next_in != -1 and next_in < groups_key[0]:
                D[key] = 0
                return 0
            while ind + 1 < len(springs) and springs[ind + 1] == '#':
                ind = ind + 1
                groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
            ans = num_possible(springs, ind + 1, in_group, groups_key)
            D[key] = ans
            return ans
    else:
        if springs[ind] == '.':
            while ind + 1 < len(springs) and springs[ind + 1] == '.':
                ind = ind + 1
            ans = num_possible(springs, ind + 1, in_group, groups_key)
            D[key] = ans
            return ans
        elif springs[ind] == '#':
            in_group = True
            groups_key = tuple([groups_key[0] - 1] + [el for el in groups_key[1:]])
            ans = num_possible(springs, ind + 1, in_group, groups_key)
            D[key] = ans
            return ans


if __name__ == "__main__":
    spring_map = load_map("input.txt")

    # print_map(spring_map)

    def compute(springs, groups_key):
        return num_possible(springs, 0, False, groups_key)

    pool = Pool(processes=8, maxtasksperchild=1)
    proc = [pool.apply_async(compute, tp) for tp in spring_map]

    pool.close()
    pool.join()

    counts = [val.get() for val in proc]
    print(f'Part 1: {sum(counts)}')

    exit(0)

    spring_map = expand(spring_map)

    print_map(spring_map)

    pool = Pool(processes=16)
    proc = [pool.apply_async(compute, tp) for tp in spring_map]

    pool.close()
    pool.join()

    counts = [val.get() for val in proc]
    print(f'Part 2: {sum(counts)}')

    exit(0)
