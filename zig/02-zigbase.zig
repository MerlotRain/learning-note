const std = @import("std");

// zig的基本数据类型和rust基本一致
// zig中的基本数据类型有：i8, i16, i32, i64, u8, u16, u32, u64, f32, f64, bool, void
// 这些类型组成了zig的底层结构
// zig的数据类型和c保持了高度一致，甚至连char都干掉了

// 离谱的东西
// zig为了兼容c，做了很多工作，比如引入了c的类型
// 同时还提供了编译时类型，这些内容会让初学者很头疼，但我们后期再讲述

test "base type" {
    const a: i32 = 123;
    const b: u32 = 456;
    const c: i64 = 789;
    const d: u64 = 123456789;
    const e: f32 = 3.14;
    const f: f64 = 2.71828;

    std.debug.print("a = {}\n", .{a});
    std.debug.print("b = {}\n", .{b});
    std.debug.print("c = {}\n", .{c});
    std.debug.print("d = {}\n", .{d});
    std.debug.print("e = {}\n", .{e});
    std.debug.print("f = {}\n", .{f});
}

test "string type" {
    const hello = "hello";
    const world = "world";

    std.debug.print("hello = {}\n", .{hello});
    std.debug.print("world = {}\n", .{world});
}

test "array type" {
    // 经典的数组定义，数组元素的类型必须一致，数组的长度也是固定的
    const array1: [5]u8 = .{ 1, 2, 3, 4, 5 };
    const array2: [5]u8 = .{ 6, 7, 8, 9, 10 };

    _ = array1;
    _ = array2;
}

test "pointer type" {
    var a: i32 = 123;
    var b: i32 = 456;
    var c: i32 = 789;

    const ptr1: *i32 = &a;
    const ptr2: *i32 = &b;
    const ptr3: *i32 = &c;

    std.debug.print("a = {}\n", .{a});
    std.debug.print("b = {}\n", .{b});
    std.debug.print("c = {}\n", .{c});

    std.debug.print("ptr1 = {}\n", .{ptr1});
    std.debug.print("ptr2 = {}\n", .{ptr2});
    std.debug.print("ptr3 = {}\n", .{ptr3});
}
