file = joinpath("c:/Users/rubendorfel/git/aoc_2023/","day_02","rd_jl", "input.txt")

lines = readlines(file)

# Define a function to extract the game and color information
function extract_colors(game)
    draws = split(strip(game), ';')
    color_list = []
    for draw in draws
        colors = split(strip(draw), ',')
        color_list = append!(color_list, colors)
    end
    return color_list
end

function game_number(game_string)
    match_result = match(r"\d+", game_string)
    digit = parse(Int, match_result.match)
    return digit
end

function extract_info(line)
    # Split the line into components
    components = split(line, ":")
    game_digit = game_number(components[1])
    color_list = extract_colors(components[2])
    return game_digit, color_list
end

function extract_color_and_digit(s)
    parts = split(s)
    color = parts[2]
    digit = parse(Int, parts[1])
    return color, digit
end

function get_possible_cubes_dict(green, blue, red)
    return Dict("green" => green, "blue" => blue, "red" => red)
end


function game_is_possible(draws, possible_cubes)
    # Call the function for each string and print the results
    for run in draws
        color, digit = extract_color_and_digit(run)
        if digit > possible_cubes[color]
            return false 
        end
    end
    return true
end

# Call the function for each line and print the results
function get_game_sum_of_possible_runs(lines, possible_cubes)
    sum = 0
    for line in lines
        game, draws = extract_info(line)
        if game_is_possible(draws, possible_cubes)
            sum = sum + game
        end
    end
    return sum
end

function compute_power(my_dict)
    product = 1
    for (key, value) in my_dict
        product = my_dict[key] * product
    end
    return product
end

function get_minimal_power(line, possible_cubes)
    game, draws = extract_info(line)
    max_cubes_used = Dict("red" => 0, "blue" => 0, "green" => 0)
    for draw in draws
        color, digit = extract_color_and_digit(draw)
        if digit > max_cubes_used[color] 
            max_cubes_used[color] = digit
        end
    end
    return compute_power(max_cubes_used)
end

function get_sum_of_minimalo_power(lines, possible_cubes)
    sum = 0
    for line in lines
        sum = sum + get_minimal_power(line, possible_cubes)
    end
    return sum
end

possible_cubes = get_possible_cubes_dict(13,14,12)

println(get_game_sum_of_possible_runs(lines, possible_cubes))
println(get_sum_of_minimalo_power(lines, possible_cubes))