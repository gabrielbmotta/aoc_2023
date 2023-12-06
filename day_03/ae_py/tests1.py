from collections import namedtuple
from helper1 import calcRowRange, calcColRange, isAdjacent, getValStr, validSymbols

testResult = namedtuple("testResult", ["valStrRes", "isAdjRes"])
def test1():
    input = ["123%\n",
             "....\n"]
    testValStr = getValStr(input[0], 0)
    expectedValStr = "123"
    ValStrResult = "Pass" if testValStr==expectedValStr else "Fail"
    testIsAdjacent = isAdjacent(input, 0, 0, len("123"))
    expectedIsAdjacent = True
    IsAdjacentResult = "Pass" if testIsAdjacent==expectedIsAdjacent else "Fail"
    result = "Pass" if "Fail" not in [ValStrResult, IsAdjacentResult] else "Fail"
    return testResult(ValStrResult, IsAdjacentResult)


def test2():
    input = ["%123\n",
             "....\n"]
    testValStr = getValStr(input[0], 1)
    expectedValStr = "123"
    ValStrResult = "Pass" if testValStr == expectedValStr else "Fail"
    testIsAdjacent = isAdjacent(input, 0, 1, len("123"))
    expectedIsAdjacent = True
    IsAdjacentResult = "Pass" if testIsAdjacent == expectedIsAdjacent else "Fail"
    result = "Pass" if "Fail" not in [ValStrResult, IsAdjacentResult] else "Fail"
    return testResult(ValStrResult, IsAdjacentResult)


def test3():
    input = [".123.\n",
             "#....\n"]
    testValStr = getValStr(input[0], 1)
    expectedValStr = "123"
    ValStrResult = "Pass" if testValStr == expectedValStr else "Fail"
    testIsAdjacent = isAdjacent(input, 0, 1, len("123"))
    expectedIsAdjacent = True
    IsAdjacentResult = "Pass" if testIsAdjacent == expectedIsAdjacent else "Fail"
    result = "Pass" if "Fail" not in [ValStrResult, IsAdjacentResult] else "Fail"
    return testResult(ValStrResult, IsAdjacentResult)


tests = [test1, test2, test3]


def runTests():
    valStrRes = []
    isAdjRes = []
    for test in tests:
        res = test()
        valStrRes.append(res.valStrRes)
        isAdjRes.append(res.isAdjRes)

    print(f"Test Results:\ngetValStr:\t{valStrRes}\nisAdjacent:\t{isAdjRes}")
