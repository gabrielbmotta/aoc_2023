const std = @import("std");

pub fn main() !void {
    var memal = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = memal.allocator();

    var bw = std.io.bufferedWriter(std.io.getStdOut().writer());
    const stdout = bw.writer();
    defer bw.flush() catch {};

    const file_path = "test.txt";
    var file = try std.fs.cwd().openFile(file_path, .{ .mode = .read_only });
    defer file.close();

    const stat = try file.stat();
    var file_data = try file.reader().readAllAlloc(allocator, stat.size);

    var lines = std.mem.tokenize(u8, file_data, "\n");
    while (lines.next()) |line| {
        try stdout.print("{s}\n", .{line});
    }

    try stdout.print("Done!\n", .{});
}
