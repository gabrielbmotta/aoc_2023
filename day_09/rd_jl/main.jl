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
    else 
        #println("go deeper")
        last = itereate_differences(differences)
    end
    return push!(last,array)
end

function get_last_value(diffs)
    lasts = []
    for diff in diffs
        lasts = append!(lasts,diff[end])
    end
    return lasts
end

function get_first_value(diffs)
    firsts = []
    for diff in diffs
        firsts = append!(firsts,diff[1])
    end
    return firsts
end

function predict_next_value(diffs)
    lasts = get_last_value(diffs)
    n_elements = length(lasts)
    nexts = lasts
    for i in 2:(n_elements)
        nexts[i] = nexts[i] + lasts[i-1]
    end
    return nexts[end]
end

function predict_previous_value(diffs)
    firsts = get_first_value(diffs)
    n_elements = length(firsts)
    nexts = firsts
    for i in 2:(n_elements)
        nexts[i] = firsts[i] - nexts[i-1]
    end
    return nexts[end]
end

function compute_sum(lines, task)
    sum = 0
    for line in lines
        array = convert_line_to_array(line)
        differences = itereate_differences(array)
        if task === 1
            next = predict_next_value(differences)
        elseif task == 2
            next = predict_previous_value(differences)
        end
        sum = sum + next
    end
    return sum
end
sum1 = compute_sum(lines, 1)
sum2 = compute_sum(lines, 2)
println("Task 1: ", sum1)
println("Task 2: ", sum2)
