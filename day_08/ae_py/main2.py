import numpy as np
from numpy import lcm


class Node():

    def __init__(self, name, L, R):
        self.name = name
        self.Lstring = L
        self.Rstring = R

    def setDirections(self, L, R):
        self.L = L
        self.R = R


allDirections, nodesText = open("input.txt", "r").read().split('\n\n')
allDirections = list(allDirections)
nodesText = nodesText.split('\n')

nodes = {}
for node in nodesText:
    name = node.split(' ')[0]
    directions = tuple(node.split('=')[1].strip().strip('()').replace(' ', '').split(','))
    nodes[name] = Node(name, *directions)
startingNodes = []
for node in nodes.values():
    node.setDirections(nodes[node.Lstring], nodes[node.Rstring])
    if node.name.endswith('A'):
        startingNodes.append(node)

stepsList = []
for node in startingNodes:
    current = node
    steps = 0
    while not current.name.endswith('Z'):
        for direction in allDirections:
            if not current.name.endswith('Z'):
                current = getattr(current, direction)
                steps += 1
    stepsList.append(steps)
answer = lcm.reduce(stepsList, dtype=np.uint64)
print(lcm.reduce(stepsList, dtype=np.uint64))
