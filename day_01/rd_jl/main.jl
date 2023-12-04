# read lines
file = joinpath("c:/Users/rubendorfel/git/aoc_2023/","day_01","rd_jl", "input.txt")

# define functions
function composeScoreLine(line)
    pattern = r"\d+"
    matches = eachmatch(pattern, line)
    numbers = []
    for match in matches
        numbers = push!(numbers,match.match)
    end
    first = numbers[1]
    last = numbers[end]
    combined = string(first[1], last[end])
    return parse(Int, combined)
end

function computeScoreDocument(lines)
    sum = 0
    for line in lines
        sum = sum + composeScoreLine(line)
    end
    return sum
end

# run
lines = readlines(file)
score = computeScoreDocument(lines)
# answer test 1 is 142
println(score)
