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

for node in nodes.values():
    node.setDirections(nodes[node.Lstring], nodes[node.Rstring])

current = nodes['AAA']
steps = 0
while current.name != "ZZZ":
    for idx, direction in enumerate(allDirections):
        print(f"At {current.name}, going {direction} to {getattr(current, direction).name}.")
        current = getattr(current, direction)
        steps += 1
        if current.name == "ZZZ":
            break
        elif steps == 19667:
            break
print(steps)
