with open("input.txt", "r") as f:
    input = f.readlines()

# find all valid symbols
validSymbols = []
for row in input:
    for char in row:
        if not char.isnumeric() and char not in ['.', '\n'] and char not in validSymbols:
            validSymbols.append(char)


def calcRowRange(input, rowIdx):
    if rowIdx == 0:  # First row in input
        startRow = 0
        endRow = rowIdx + 1
    elif rowIdx == len(input) - 1:  # Last row in input
        startRow = rowIdx - 1
        endRow = rowIdx
    else:  # Any other row
        startRow = rowIdx - 1
        endRow = rowIdx + 1

    return range(startRow, endRow + 1)


def calcColRange(input, colIdx, valLen):
    if colIdx == 0:  # First char in line
        startCol = colIdx
        endCol = colIdx + valLen
    elif (colIdx == len(input) - 1  # Last char in line
          or colIdx + valLen - 1 == len(input)):  # Or last value in number is last char in line
        startCol = colIdx - 1
        endCol = colIdx + valLen - 1
    else:  # Any other char
        startCol = colIdx - 1
        endCol = colIdx + valLen

    return range(startCol, endCol + 1)


def isAdjacent(input, rowIdx, colIdx, valLen):
    rowRange = calcRowRange(input, rowIdx)
    colRange = calcColRange(input, colIdx, valLen)

    for row in rowRange:
        for col in colRange:
            if input[row][col] in validSymbols:
                return True

    return False


def getValStr(line, colIdx):
    i = 0
    valStr = ''
    while (line[colIdx + i] != '\n' # While not at end of line
           and line[colIdx + i] not in validSymbols # Iterate through line until we hit a valid symbol
           and line[colIdx + i] != '.'):  # Or until we hit a '.'
        valStr = valStr + (line[colIdx + i])
        i += 1
    return valStr
