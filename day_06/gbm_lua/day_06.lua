local infile = assert(io.open("input.txt", "r"))
io.input(infile)

local function line_as_list()
    local line = io.read("*line")
    local items = {}
    for item in line:gmatch("%d*") do table.insert(items, tonumber(item)) end
    return items
end

local times = line_as_list()
local dists = line_as_list()

local function num_winning(time, dist)
    local d = (time * time) - (4 * -1 * -dist)
    local x1 = (-time + math.sqrt(d)) / -2
    local x2 = (-time - math.sqrt(d)) / -2
    return math.ceil(x2) - math.floor(x1) - 1
end

local part_1_prod = 1
for i, _ in pairs(times) do
    part_1_prod = part_1_prod * num_winning(times[i], dists[i])
end

local part_2 = num_winning(tonumber(table.concat(times)), tonumber(table.concat(dists)))

print(string.format("Part 1: %d", part_1_prod))
print(string.format("Part 2: %d", part_2))

