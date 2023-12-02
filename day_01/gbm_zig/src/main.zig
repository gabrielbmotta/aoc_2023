const std = @import("std");

var memal = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = memal.allocator();

const digit_names = std.ComptimeStringMap(u8, .{
    .{ "one", '1' },   .{ "two", '2' },   .{ "three", '3' },
    .{ "four", '4' },  .{ "five", '5' },  .{ "six", '6' },
    .{ "seven", '7' }, .{ "eight", '8' }, .{ "nine", '9' },
});

const substr_list: [18][]const u8 = .{ "1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

fn digit_name(number: []const u8) u8 {
    return digit_names.get(number).?;
}

fn digits_as_number(num: struct { i32, i32 }) i32 {
    return 10 * num[0] + num[1];
}

fn first_last_digit(source_str: []const u8, accept_text: bool) !struct { i32, i32 } {
    var first_inst: usize = std.math.maxInt(usize);
    var first_val: i32 = undefined;
    var last_inst: usize = std.math.minInt(usize);
    var last_val: i32 = undefined;

    for (substr_list) |substr| {
        if (accept_text == false and substr.len > 1) continue;

        var ind: usize = std.mem.indexOf(u8, source_str, substr) orelse continue;
        if (ind < first_inst) {
            first_inst = ind;
            const digit = if (substr.len > 1) digit_name(substr) else substr[0];
            first_val = try std.fmt.charToDigit(digit, 10);
        }
        ind = std.mem.lastIndexOf(u8, source_str, substr) orelse continue;
        if (ind >= last_inst) {
            last_inst = ind;
            const digit = if (substr.len > 1) digit_name(substr) else substr[0];
            last_val = try std.fmt.charToDigit(digit, 10);
        }
    }
    return .{ first_val, last_val };
}

pub fn main() !void {
    var bw = std.io.bufferedWriter(std.io.getStdOut().writer());
    const stdout = bw.writer();
    defer bw.flush() catch {};

    const file_path = "input.txt";
    var file = try std.fs.cwd().openFile(file_path, .{ .mode = .read_only });
    const stat = try file.stat();
    const file_data = try file.reader().readAllAlloc(allocator, stat.size);

    var lines = std.mem.tokenize(u8, file_data, "\n");
    var rolling_sum1: i32 = 0;
    var rolling_sum2: i32 = 0;
    while (lines.next()) |line| {
        rolling_sum1 += digits_as_number(try first_last_digit(line, false));
        rolling_sum2 += digits_as_number(try first_last_digit(line, true));
    }

    try stdout.print("Part 1: {}\nPart 2: {}\n", .{ rolling_sum1, rolling_sum2 });
}
