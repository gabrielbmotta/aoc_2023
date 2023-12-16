from collections import namedtuple
class mapObj():

    def __init__(self, mapName, mapLines):
        self.name = mapName
        self.fullMap = mapLines

    def traverse(self, ranges):
        """Function to apply all map lines in map to all input ranges.
        Any new resulting ranges due to overlaps are added to a list and returned.

        ranges - list of seed ranges to which all map lines are applied
        """
        destinations = []
        for mapDest, mapSrc, mapSize in self.fullMap:
            mapEnd = mapSrc + mapSize
            newRanges = []
            while ranges:
                rangeStart, rangeStop = ranges.pop() # remove range under assessment to prevent duplicates
                # Calculate intersections of seed range with map line
                # This can result in up to 3 segments, if the map line is a subset of the seed range
                # These 3 segments are defined as:
                #     From the start of the seed range to the start of the map line or end of the seed range (only if seed range is completely inside the map line)
                #     From the start of the map line to the end of the map line or seed range
                #     From the end of the map line to the end of the seed range (only if the map line is completely inside the seed range
                # Up to 2 of these segments can be empty, if the seed and map line don't intersect
                # For each non-intersecting segment, a new range should be added to a list to be applied to all other map lines in the map
                before = (rangeStart, min(mapSrc, rangeStop))
                intersect = (max(rangeStart, mapSrc), min(rangeStop, mapEnd))
                after = (max(rangeStart, mapEnd), rangeStop)
                if before[1] > before[0]:  # if the before range exists, add it to new ranges
                    newRanges.append(before)
                if intersect[1] > intersect[0]:  # if the intersect range exists, traverse the mapped region and add the resulting range to final output
                    destinations.append((intersect[0] + mapDest - mapSrc, intersect[1] + mapDest - mapSrc))
                if after[1] > after[0]:  # if the after range exists, add it to new ranges
                    newRanges.append(after)
            ranges = newRanges  # once ranges is exhaused, add new range fragments for mapping by remaining map lines
        destinations += ranges  # add ranges which did not intersect with any map lines to destinations
        return destinations


def getSeedRanges(input):
    seedNums = [int(x) for x in input.split(":")[1].strip().split(" ")]
    seedRanges = []
    for idx in range(len(seedNums) // 2):
        seedStart = seedNums[2 * idx]
        seedRange = seedNums[2 * idx + 1]
        seedRanges.append(range(seedStart, seedStart + seedRange))
    return seedRanges


def getMaps(input):
    maps = []
    mapLines = []
    for line in input:
        if ":" in line:
            mapName = line.split(" ")[0]
        elif line[0].isnumeric():
            mapLines.append([int(x) for x in line.split(" ")])
        else:
            maps.append(mapObj(mapName, mapLines))
            mapName = ""
            mapLines = []
    maps.append(mapObj(mapName, mapLines))
    return maps
