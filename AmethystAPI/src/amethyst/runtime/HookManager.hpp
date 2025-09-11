#pragma once
#include "amethyst-deps/safetyhook.hpp"
#include "amethyst/Log.hpp"
#include "amethyst/Memory.hpp"
#include "minecraft/src-deps/core/string/StringHash.hpp"
#include <unordered_map>
#include <vector>

#define NO_THROW_HOOK(className, functionName, signature)                                                                  \
{                                                                                                                      \
    auto scan = SigScanSafe(signature);                                                                                \
    if (!scan.has_value())                                                                                             \
        Log::Warning("[SAFE_HOOK] SigScan failed for {}::{}, signature = {}", #className, #functionName, signature);   \
    else {                                                                                                             \
        hookManager->RegisterFunction<&className::functionName>(scan.value());                                         \
        hookManager->CreateHook<&className::functionName>(_##className##_##functionName, &className##_##functionName); \
    }                                                                                                                  \
}

namespace Amethyst {
    class function_id {
    public:
        template <auto Fn>
        static consteval uint64_t hash_code()
        {
            return HashedString::computeHash(name<Fn>());
        }

        template <auto Fn>
        static consteval std::string_view name() {
            constexpr std::string_view funcSig = __FUNCSIG__;
            constexpr std::string_view prefix = "function_id::name<";
            constexpr std::size_t begin = funcSig.find("function_id::name<");
            constexpr std::size_t end = funcSig.rfind('>');
            static_assert(begin != std::string_view::npos);
            static_assert(end != std::string_view::npos);
            return funcSig.substr(begin + prefix.size(), end - begin - prefix.size());
        }

        template<typename T>
        static consteval uint64_t class_hash() {
            constexpr std::string_view name = __FUNCSIG__;
            return HashedString::computeHash(name);
        }
    };

    class HookManager {
    public:
        template <auto OriginalFn>
        void CreateHook(SafetyHookInline& trampoline, void* hook)
        {
            constexpr size_t hash = function_id::hash_code<OriginalFn>();

            Assert(mFuncHashToOriginalAddress.contains(hash), "[AmethystAPI] '{}' has not registered!", function_id::name<OriginalFn>());

            uintptr_t original_addr = mFuncHashToOriginalAddress[hash];
            CreateHookAbsolute(trampoline, original_addr, hook);
        }

        template <auto OriginalFn>
        void CreateDirectHook(SafetyHookInline& trampoline, void* hook)
        {
            uintptr_t original_addr = std::bit_cast<uintptr_t>(OriginalFn);
            CreateHookAbsolute(trampoline, original_addr, hook);
        }

        template <auto OriginalFn>
        void CreateVirtualHook(uintptr_t vtable, SafetyHookInline& trampoline, void* hook)
        {
            size_t offset = GetVirtualFunctionOffset<OriginalFn>();
            uintptr_t vtableEntry = reinterpret_cast<uintptr_t*>(vtable)[offset / sizeof(void*)];
            CreateHookAbsolute(trampoline, vtableEntry, hook);
        }

        /**
         * Directly replaces a virtual function in a virtual table
         * CAUTION: This will not work if two mods want to replace the same function. For more compatibility, use HookManager::CreateVirtualHook
         */
        template <auto OriginalFn>
        uintptr_t ReplaceVirtualFunction(uintptr_t vtable, void* newFunction)
        {
            size_t offset = GetVirtualFunctionOffset<OriginalFn>();
            uintptr_t* vtablePtr = reinterpret_cast<uintptr_t*>(vtable);
            uintptr_t& function = vtablePtr[offset / sizeof(void*)];
            uintptr_t original = function;
            DWORD oldProt;
            UnprotectMemory(reinterpret_cast<uintptr_t>(&function), sizeof(uintptr_t), &oldProt);
            function = reinterpret_cast<uintptr_t>(newFunction);
            ProtectMemory(reinterpret_cast<uintptr_t>(&function), sizeof(uintptr_t), oldProt);
            return original;
        }

        /**
         * Directly hooks a function with an absolute address
         * CAUTION: This will not work if two mods want to hook the same function. For more compatibility, use HookManager::CreateHook
         */
        void CreateHookAbsolute(SafetyHookInline& safetyHookTrampoline, uintptr_t originalAddress, void* hook)
        {
            safetyHookTrampoline = safetyhook::create_inline((void*)originalAddress, hook);
            mHooks.push_back(&safetyHookTrampoline);
        }

        template <auto Func>
        void RegisterFunction(std::string_view signature)
        {
            // Converts the function to a unique hashed number
            constexpr size_t hash = function_id::hash_code<Func>();

            // If the event has not yet been created, make it, else re-use
            if (!mFuncHashToOriginalAddress.contains(hash)) {
                auto result = SigScanSafe(signature);

                Assert(result.has_value(), "Failed to find function: \"{}\"\nUsing signature: \"{}\"", function_id::name<Func>(), signature);

                mFuncHashToOriginalAddress[hash] = result.value();
            }
        }

        template <auto Func>
        void RegisterFunction(uintptr_t address)
        {
            // Converts the function to a unique hashed number
            constexpr size_t hash = function_id::hash_code<Func>();

            // If the event has not yet been created, make it, else re-use
            if (!mFuncHashToOriginalAddress.contains(hash)) {
                mFuncHashToOriginalAddress[hash] = address;
            }
        }

        ~HookManager();

    private:
        std::vector<SafetyHookInline*> mHooks;
        std::unordered_map<size_t, uintptr_t> mFuncHashToOriginalAddress;
        friend class AmethystRuntime;
    };
} // namespace Amethyst