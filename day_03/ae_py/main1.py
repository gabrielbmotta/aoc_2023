from helper1 import calcRowRange, calcColRange, isAdjacent, getValStr, validSymbols
from tests1 import runTests

runTests()

with open("input.txt", "r") as f:
    input = f.readlines()

sum = 0
for rowIdx, line in enumerate(input):
    skipChars = 0
    for colIdx, char in enumerate(line):
        skipChars = skipChars - 1 if skipChars else skipChars
        if char.isnumeric() and not skipChars:  # If we find a number that isn't part of a previously discovered number
            valStr = getValStr(line, colIdx)  # Get the full number
            skipChars = len(valStr)  # Skip the rest of the number
            if isAdjacent(input, rowIdx, colIdx, len(valStr)):
                sum+=int(valStr)

print(sum)
