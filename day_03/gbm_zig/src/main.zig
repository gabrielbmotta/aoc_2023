const std = @import("std");

var memal = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = memal.allocator();

var bw = std.io.bufferedWriter(std.io.getStdOut().writer());
const stdout = bw.writer();

fn sum_of_part_numbers(schematic: *std.ArrayList(std.ArrayList(u8))) !i32 {
    var part_sum: i32 = 0;

    var skip: i32 = 0;

    for (schematic.*.items, 0..) |i_r, i| {
        for (i_r.items, 0..) |j_r, j| {
            if (skip > 0) {
                skip -= 1;
                continue;
            }
            if (std.ascii.isDigit(j_r)) {
                skip = -1;
                var ind: usize = j;
                var valid: bool = false;
                var num: i32 = 0;
                while (std.ascii.isDigit(schematic.*.items[i].items[ind])) {
                    try stdout.print("found {c}\n", .{j_r});
                    if (valid_location(schematic, i, ind)) {
                        valid = true;
                    }
                    num = 10 * num + try std.fmt.charToDigit(schematic.*.items[i].items[ind], 10);
                    ind = ind + 1;
                    skip += 1;
                }
                if (valid) {
                    part_sum += num;
                    try stdout.print("found {c}\n", .{j_r});
                    stdout.print("sum now {}\n", .{part_sum}) catch {};
                }
            }
        }
    }
    return part_sum;
}

fn valid_location(
    schematic: *std.ArrayList(std.ArrayList(u8)),
    i: usize,
    j: usize,
) bool {
    var x: i32 = -1;
    var y: i32 = -1;
    while (x < 2) {
        while (y < 2) {
            var ind_x: i32 = @intCast(i);
            ind_x += x;
            var ind_y: i32 = @intCast(j);
            ind_y += y;

            if (ind_y < 0 or ind_y >= schematic.*.items.len) {
                continue;
            }
            if (ind_x < 0 or ind_x > schematic.*.items[0].items.len) {
                continue;
            }

            if (schematic.*.items[@intCast(ind_x)].items[@intCast(ind_y)] != '.' and !std.ascii.isDigit(schematic.*.items[@intCast(ind_x)].items[@intCast(ind_y)])) {
                return true;
            }
            y += 1;
        }
        x += 1;
    }

    return false;
}

fn get_full_number(
    schematic: *std.ArrayList(std.ArrayList(u8)),
    i: usize,
    j: usize,
) !i32 {
    var first_dig_ind: usize = i;
    while (first_dig_ind > 0 and std.ascii.isDigit(schematic.*.items[first_dig_ind - 1].items[j])) {
        first_dig_ind -= 1;
    }

    var num: i32 = 0;

    while (first_dig_ind < schematic.*.items[0].items.len and std.ascii.isDigit(schematic.*.items[first_dig_ind].items[j])) {
        num = 10 * num + try std.fmt.charToDigit(schematic.*.items[first_dig_ind].items[j], 10);
        first_dig_ind += 1;
    }

    stdout.print("getting num {}\n", .{num}) catch {};
    return num;
}

pub fn main() !void {
    defer bw.flush() catch {};

    const file_path = "input.txt";
    var file = try std.fs.cwd().openFile(file_path, .{ .mode = .read_only });
    const stat = try file.stat();
    const file_data = try file.reader().readAllAlloc(allocator, stat.size);
    var line_len = std.mem.indexOf(u8, file_data, "\n").?;
    var schematics: std.ArrayList(std.ArrayList(u8)) = std.ArrayList(std.ArrayList(u8)).init(allocator);

    var lines = std.mem.tokenizeSequence(u8, file_data, "\n");
    while (lines.next()) |line| {
        var temp_line: std.ArrayList(u8) = std.ArrayList(u8).init(allocator);

        for (line) |ch| {
            if (ch == '\n') break;
            try temp_line.append(ch);
        }
        try schematics.append(temp_line);
    }

    var part_sum = try sum_of_part_numbers(&schematics);

    try stdout.print("Sum: {any}\n", .{part_sum});
    try stdout.print("Line len: {any}\n", .{line_len});
    try stdout.print("Col height : {any}\n", .{schematics.items.len});
}
