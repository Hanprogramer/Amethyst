#pragma once
#include "amethyst/Log.hpp"
#include <chrono>
#include <cstdint>
#include <psapi.h>
#include <string>
#include <vector>
#include <string_view>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/*
Returns the position where Minecraft has been loaded into memory
*/
uintptr_t GetMinecraftBaseAddress();

/*
Returns the size of the game (in bytes) while loaded in memory
*/
unsigned long GetMinecraftSize();

/*
Offsets an address from the game binary, with the position the game has been loaded into memory at
*/
uintptr_t SlideAddress(uintptr_t offset);

/*
Finds an address of a function with its signature within the loaded game memory
*/
std::optional<uintptr_t> SigScanSafe(std::string_view signature);

/*
Finds an address of a function with its signature within the loaded game memory
*/
uintptr_t SigScan(std::string_view signature);

/**
 * Finds the offset of a pointer in a struct/class
 * returns SIZE_MAX if it fails
*/
size_t FindOffsetOfPointer(void* _base, void* _pointer, size_t maxSearchSize);

/**
 * Unprotects the memory region 
*/
void UnprotectMemory(uintptr_t address, size_t size, DWORD* oldProtection);

/**
 * Reprotects the memory region
*/
void ProtectMemory(uintptr_t address, size_t size, DWORD protectionData, DWORD* oldProtection = nullptr);

/*
 * Returns the offset (in loaded memory space), to a pointer in a lea instruction
 */
uintptr_t AddressFromLeaInstruction(uintptr_t leaInstructionAddress);

uintptr_t GetVtable(void* obj);

/*
 * Returns the virtual offset of a virtual function from a thunk
 */

template <auto T>
size_t GetVirtualFunctionOffset() {
    uintptr_t func = std::bit_cast<uintptr_t>(T);
    uint8_t* bytes = reinterpret_cast<uint8_t*>(func);
    if (bytes[0] != 0xE9) {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Not a valid thunk! (Expected 0xE9 (jmp), got {:X})", bytes[0]);
        return 0;
    }

    func = *reinterpret_cast<uint32_t*>(bytes + 1) + func + 5;
    bytes = reinterpret_cast<uint8_t*>(func) + 3;

    if (bytes[0] != 0xFF) {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Not a valid thunk! (Expected 0xFF (jmp), got {:X})", bytes[0]);
        return 0;
    }

    uint8_t modrm = bytes[1];
    if (modrm == 0x60) {
        return bytes[2];
    }
    else if (modrm == 0xA0) {
        return *reinterpret_cast<uint32_t*>(bytes + 2);
    }
    else {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Not a valid thunk! (Unknown ModRM byte {:X})", modrm);
    }

    return 0;
}