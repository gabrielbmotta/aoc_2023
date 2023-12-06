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


def calcColRange(input, colIdx):
    if colIdx == 0:  # First char in line
        startCol = colIdx
        endCol = colIdx + 1
    elif colIdx == len(input) - 1:  # Last char in line
        startCol = colIdx - 1
        endCol = colIdx
    else:  # Any other char
        startCol = colIdx - 1
        endCol = colIdx + 1

    return range(startCol, endCol + 1)

def getAdjacents(input, rowIdx, colIdx):
    vals = []
    for row in calcRowRange(input, rowIdx):
        skipChars = 0
        for col in calcColRange(input, colIdx):
            if input[row][col].isnumeric() and not skipChars:
                # Find the beginning of the adjacent number
                numStartIdx = col
                while input[row][numStartIdx].isnumeric():
                    numStartIdx -= 1
                numStartIdx += 1  # numStartIdx decremented to a non-number char, so increment it
                numEndIdx = col
                while input[row][numEndIdx].isnumeric():
                    numEndIdx += 1
                vals.append(input[row][numStartIdx:numEndIdx])
                skipChars = numEndIdx - col - 1
            elif skipChars > 0:
                skipChars -= 1
    return vals
