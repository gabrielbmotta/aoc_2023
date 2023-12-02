const std = @import("std");

var memal = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = memal.allocator();

var bw = std.io.bufferedWriter(std.io.getStdOut().writer());
const stdout = bw.writer();

fn game_value(source_str: []const u8, num_red: i32, num_green: i32, num_blue: i32) !i32 {
    const dec_mult: i32 = 10;
    var game_ind: i32 = 0;

    for (source_str[5..]) |ch| {
        if (ch == ':') break;
        try stdout.print("{c}", .{ch});
        game_ind = game_ind * dec_mult + try std.fmt.charToDigit(ch, 10);
    }

    try stdout.print("   ", .{});
    var map = std.AutoHashMap(u8, i32).init(allocator);
    try map.put('d', num_red);
    try map.put('n', num_green);
    try map.put('e', num_blue);

    const col_ind: usize = std.mem.indexOf(u8, source_str, ":") orelse return 0;

    var games = std.mem.tokenize(u8, source_str[col_ind + 1 ..], ";");

    while (games.next()) |game| {
        var entries = std.mem.tokenize(u8, game, ",");
        while (entries.next()) |entry| {
            var amount: i32 = 0;
            for (entry[1..]) |ch| {
                if (ch == ' ') break;
                amount = amount * dec_mult + try std.fmt.charToDigit(ch, 10);
            }

            try stdout.print("|{s}| ", .{entry});
            // try stdout.print("{any} ", .{amount});
            // try stdout.print("[{}] ", .{map.get(entry[entry.len - 1]) orelse std.math.maxInt(i32)});

            if (amount > map.get(entry[entry.len - 1]) orelse std.math.maxInt(i32)) {
                // try stdout.print("Game {}: ", .{game_ind});
                // try stdout.print("amt higher {} ", .{amount});
                // try stdout.print("map val {} ", .{map.get(entry[entry.len - 1]) orelse 0});
                return 0;
            }
        }
    }

    try stdout.print("adding {any} -> ", .{game_ind});
    return game_ind;
}

pub fn main() !void {
    defer bw.flush() catch {};

    const file_path = "input.txt";
    var file = try std.fs.cwd().openFile(file_path, .{ .mode = .read_only });
    const stat = try file.stat();
    const file_data = try file.reader().readAllAlloc(allocator, stat.size);
    var lines = std.mem.tokenize(u8, file_data, "\n");

    var sum: i32 = 0;
    while (lines.next()) |line| {
        sum += try game_value(line, 12, 13, 14);
        try stdout.print("{any}\n", .{sum});
    }
}
