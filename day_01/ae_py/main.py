def stringToNum(line):
    numStrings = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
    numStringsMap = dict(zip(numStrings, range(0, 10)))
    replaced = 0
    firstNum = None
    lastNum = None
    # Iterate thru line left to right
    for idx in range(len(line)):
        # Check if integer is encountered
        if not line[idx].isnumeric():
            # For each character, check if any number string starts at this index
            for val in numStrings:
                # If number string found
                if line[idx:idx + len(val)] == val:
                    # Save integer value of number string and break
                    firstNum = str(numStringsMap[val])
                    replaced = 1
                    break
            # Breaking out of nested loops is suffering
            if replaced:
                break
        # If integer encountered, save and break
        else:
            firstNum = line[idx]
            break
    replaced = 0

    # Iterate thru line right to left
    for idx in reversed(range(len(line))):
        # Check if integer is encountered
        if not line[idx].isnumeric():
            # For each character, check if any number string ends at this index
            for val in numStrings:
                # If number string found
                if line[idx - len(val) + 1:idx + 1] == val:
                    # Save integer value of number string and break
                    lastNum = str(numStringsMap[val])
                    replaced = 1
                    break
            if replaced:
                break
        # If integer encountered, save and break
        else:
            lastNum = line[idx]
            break

    # This only happens if the last index is skipped iterating forward or
    # the first index is skipped iterating backward
    if None in (firstNum, lastNum):
        print("You messed up a looping condition")

    return int(firstNum + lastNum)


def main():
    with open("input.txt", "r") as f:
        input = f.readlines()
    answer = 0

    # Janky unit tests
    test1 = "2eightwotg"
    test1out = stringToNum(test1)
    expected1 = 22
    result1 = "Pass" if test1out == expected1 else "Fail"
    print(f"Test 1: {result1}")

    test2 = "asdf3asdf"
    test2out = stringToNum(test2)
    expected2 = 33
    result2 = "Pass" if test2out == expected2 else "Fail"
    print(f"Test 2: {result2}")

    test3 = "eightwone"
    test3out = stringToNum(test3)
    expected3 = 81
    result3 = "Pass" if test3out == expected3 else "Fail"
    print(f"Test 3: {result3}")

    test4 = "3gngzkpkgrf"
    test4out = stringToNum(test4)
    expected4 = 33
    result4 = "Pass" if test4out == expected4 else "Fail"
    print(f"Test 4: {result4}")

    for line in input:
        print("Input line: " + line[:-1])
        val = stringToNum(line)
        print("Recovered value: " + str(val) + "\n")
        answer += val
    print(answer)


main()
