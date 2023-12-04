# read lines
file = joinpath("c:/Users/rubendorfel/git/aoc_2023/","day_01","rd_jl", "input.txt")

# define functions
function isNotDigit(a)
    return tryparse(Int, a) === nothing
end

function combineFirstAndLastNumber(numbers)
    first = numbers[1]
    last = numbers[end]
    combined = string(first[1], last[end])
    return parse(Int, combined)
end

function convertWordToDigit(number)
    num_dict = Dict("zero" => "0", "one" => "1", "two" => "2", "three" => "3", "four" => "4", "five" => "5", "six" => "6", "seven" => "7", "eight" => "8", "nine" => "9")
    return num_dict[number]
end

function getAllPotentialNumbers(line)
    pattern = r"one|two|three|four|five|six|seven|eight|nine|\d+"
    return eachmatch(pattern, line, overlap=true)
end

function getNumber(match)
    number = match.match
    if isNotDigit(number)
        number = convertWordToDigit(number)
    end
    return number
end

function extractNumbersFromMatches(matches)
    numbers = []
    for match in matches
        number = getNumber(match)
        numbers = push!(numbers,number)
    end
    return numbers
end

function composeScoreLine(line)
    matches = getAllPotentialNumbers(line)
    numbers = extractNumbersFromMatches(matches)
    return combineFirstAndLastNumber(numbers)
end

function computeScoreDocument(lines)
    sum = 0
    for line in lines
        score = composeScoreLine(line)
        sum = sum + score
    end
    return sum
end

# run
lines = readlines(file)
score = computeScoreDocument(lines)
# answer test 1 is 142; test 2 is 281
println(score)

