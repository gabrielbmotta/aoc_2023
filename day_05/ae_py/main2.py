from helper2 import mapObj, getSeedRanges, getMaps

if __name__ == '__main__':
    with open("input.txt", "r") as f:
        input = f.readlines()

    # Get seeds
    seedRanges = getSeedRanges(input[0])

    # Get maps
    maps = getMaps(input[2:])

    for seedRange in seedRanges:
        ranges = [(seedRange.start, seedRange.stop)]  # initalize ranges list with first seed range
        for map in maps:
            ranges = map.traverse(ranges)

    print(min(ranges)[0])  # print lowest value in lowest desination range