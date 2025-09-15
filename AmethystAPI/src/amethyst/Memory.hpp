#pragma once
#include "amethyst-deps/Zydis.h"
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
__declspec(noinline) size_t GetVirtualFunctionOffset() {
    uintptr_t func = std::bit_cast<uintptr_t>(T);
    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    ZydisDecodedInstruction instr;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];

    // Decode jmp rel32
    if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
        if (instr.mnemonic == ZYDIS_MNEMONIC_JMP && instr.operand_count == 2 && operands[0].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) {
            func += instr.length + operands[0].imm.value.s;
        }
    }
    else {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
        return 0;
    }

    
    if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
        // Decode first instruction (mov rax, ...)
        if (instr.mnemonic == ZYDIS_MNEMONIC_MOV) {
            func += instr.length;
            if (!ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
                Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
                return 0;
            }
        }
        
        // Decode second instruction (jmp [rax+disp])
        if (instr.mnemonic != ZYDIS_MNEMONIC_JMP || operands[0].type != ZYDIS_OPERAND_TYPE_MEMORY) {
            Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Expected jmp [rax+disp] instruction.");
            return 0;
        }

        const auto& mem = operands[0].mem;
        if (mem.base != ZYDIS_REGISTER_RAX) {
            Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Expected base register to be RAX.");
            return 0;
        }

        // disp.value holds either disp8 or disp32 already sign-extended
        return static_cast<size_t>(mem.disp.value);
    }
    else {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
    }
    return 0;
}