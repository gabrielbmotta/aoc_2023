file = joinpath("c:/Users/rubendorfel/git/aoc_2023/","day_08","rd_jl", "input.txt")

lines = readlines(file)

function get_instructions(lines)
    instruction_lookup = Dict('L' => 1 , 'R' => 2)
    instructions = collect(lines[1])
    return map(x -> instruction_lookup[x], instructions)
end

function convert_value_to_array(string)
    matches = eachmatch(r"[A-Z]+", string)
    return [m.match for m in matches]
end
function get_network_entry(line)
    key_values = split(line," = ")

    return key_values[1], convert_value_to_array(key_values[2])
end

function get_network(lines)
    n_lines = length(lines)
    network = Dict()
    for i in 3:n_lines
        key, value = get_network_entry(lines[i]) 
        network[key] = value
    end
    return network
end

function navigate_network(network, instructions)
    nsteps = 0
    current_field = "AAA"
    stop = "ZZZ"
    while current_field !== stop
        for direction in instructions
            nsteps = nsteps + 1
            current_field = network[current_field][direction]
            if current_field == stop
                return nsteps
            end
        end
    end
end

instructions = get_instructions(lines)
network = get_network(lines)
nsteps = navigate_network(network, instructions)
println(nsteps)