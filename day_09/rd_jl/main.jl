file = joinpath("c:/Users/rubendorfel/git/aoc_2023/","day_09","rd_jl", "input.txt")

lines = readlines(file)

function convert_line_to_array(line)
    numbers = split(line, " ")
    integers = parse.(Int, numbers)
    return integers
end

function compute_difference(array)
    n_elements = length(array)
    differences = []
    for i in 1:(n_elements-1)
        differences = append!(differences,array[i+1] - array[i])
    end
    return differences
end

function is_all_zero(array)
    return all(array .== 0)
end

function itereate_differences(array)
    differences = compute_difference(array)
    last = []
    if is_all_zero(array)
        #println("go up again")
        last = append!(last,array[end])
    else 
        #println("go deeper")
        last = itereate_differences(differences)
        last = append!(last,array[end])
    end
    return last
end

function predict_next_value(diffs)
    n_elements = length(diffs)
    nexts = diffs
    for i in 2:(n_elements)
        nexts[i] = nexts[i] + diffs[i-1]
    end
    return nexts[end]
end

function compute_sum(lines)
    sum = 0
    for line in lines
        array = convert_line_to_array(line)
        last_differences = itereate_differences(array)
        next = predict_next_value(last_differences)
        sum = sum + next
    end
    return sum
end

sum = compute_sum(lines)
println("Task 1: ", sum)