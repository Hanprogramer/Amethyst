#pragma once

enum class ItemContextFlags : unsigned char {
    None = 0x0000,
    FirstPersonPass = 0x0001,
    WorldPass = 0x0002,
    UIPass = 0x0004,
    Item2D = 0x0008,
    Item3D = 0x0010,
    InHand = 0x0020,
    Glint = 0x0040,
    MultiColorTint = 0x0080,
};