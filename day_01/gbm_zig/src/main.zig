const std = @import("std");

var memal = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = memal.allocator();

fn sum_first_last(file: std.fs.File) i32 {
    const stat = file.stat() catch {
        return 0;
    };
    var file_data = file.reader().readAllAlloc(allocator, stat.size) catch {
        return 0;
    };

    var lines = std.mem.tokenize(u8, file_data, "\n");
    var rolling_sum: i32 = 0;
    while (lines.next()) |line| {
        var first_digit: i32 = for (line) |ch| {
            if (ch >= '0' and ch <= '9') {
                break ch - '0';
            }
        };
        var running_last: i32 = first_digit;
        for (line) |ch| {
            if (ch >= '0' and ch <= '9') {
                running_last = ch - '0';
            }
        }
        rolling_sum += 10 * first_digit + running_last;
    }
    return rolling_sum;
}

fn to_numbers_only(string: []const u8) ![]u8 {
    var new_str = try allocator.dupe(u8, string);
    _ = std.mem.replace(u8, new_str, "one", "o1e", new_str);
    _ = std.mem.replace(u8, new_str, "two", "t2o", new_str);
    _ = std.mem.replace(u8, new_str, "three", "th3ee", new_str);
    _ = std.mem.replace(u8, new_str, "four", "fo4r", new_str);
    _ = std.mem.replace(u8, new_str, "five", "fi5w", new_str);
    _ = std.mem.replace(u8, new_str, "six", "s6x", new_str);
    _ = std.mem.replace(u8, new_str, "seven", "se7en", new_str);
    _ = std.mem.replace(u8, new_str, "eight", "ei8ht", new_str);
    _ = std.mem.replace(u8, new_str, "nine", "ni9e", new_str);

    return new_str;
}

fn sum_first_last_fancy(file: std.fs.File) !i32 {
    const stat = file.stat() catch {
        return 0;
    };
    var file_data = file.reader().readAllAlloc(allocator, stat.size) catch {
        return 0;
    };

    var lines = std.mem.tokenize(u8, file_data, "\n");
    var rolling_sum: i32 = 0;
    while (lines.next()) |line_p| {
        var line = try to_numbers_only(line_p);
        var first_digit: i32 = for (line) |ch| {
            if (ch >= '0' and ch <= '9') {
                break ch - '0';
            }
        };
        var running_last: i32 = first_digit;
        for (line) |ch| {
            if (ch >= '0' and ch <= '9') {
                running_last = ch - '0';
            }
        }
        rolling_sum += 10 * first_digit + running_last;
    }
    return rolling_sum;
}

pub fn main() !void {
    var bw = std.io.bufferedWriter(std.io.getStdOut().writer());
    const stdout = bw.writer();
    defer bw.flush() catch {};

    const file_path = "input.txt";
    var file = try std.fs.cwd().openFile(file_path, .{ .mode = .read_only });

    const part_1 = sum_first_last(file);
    try stdout.print("Part 1: {}\n", .{part_1});
    file.close();

    var file2 = try std.fs.cwd().openFile(file_path, .{ .mode = .read_only });
    defer file2.close();
    const part_2 = try sum_first_last_fancy(file2);
    try stdout.print("Part 2: {}\n", .{part_2});
}
