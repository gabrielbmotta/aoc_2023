from collections import namedtuple

mapLine = namedtuple("mapLine", ("outputStart", "inputStart", "mapRange"))


class mapObj():

    def __init__(self, mapName, mapLines):
        self.name = mapName
        self.fullMap = mapLines

    def traverse(self, input):
        for mapLine in self.fullMap:
            if input in range(mapLine.inputStart, mapLine.inputStart + mapLine.mapRange):
                return mapLine.outputStart + (input - mapLine.inputStart)
        return input
