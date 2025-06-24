#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/MinecraftVtables.hpp>
#include <minecraft/src/common/Minecraft.hpp>

static AmethystContext* _AmethystContextInstance;

void Amethyst::InitializeAmethystMod(AmethystContext& context)
{
    // Initialize vtbl pointers & ctor pointers.
    InitializeVtablePtrs();

    // Store a persistent AmethystContext instance
    _AmethystContextInstance = &context;
}

AmethystContext& Amethyst::GetContext()
{
    return *_AmethystContextInstance;
}

Amethyst::EventBus& Amethyst::GetEventBus()
{
    return *_AmethystContextInstance->mEventBus.get();
}

Amethyst::HookManager& Amethyst::GetHookManager()
{
    return *_AmethystContextInstance->mHookManager.get();
}

Amethyst::PatchManager& Amethyst::GetPatchManager()
{
    return *_AmethystContextInstance->mPatchManager.get();
}

Amethyst::EnumAllocator& Amethyst::GetEnumAllocator()
{
    return *_AmethystContextInstance->mEnumAllocator.get();
}

Amethyst::SymbolLoader& Amethyst::GetSymbolLoader()
{
    if (_AmethystContextInstance == nullptr) {
        HMODULE runtimeDll = GetModuleHandleA("AmethystRuntime.dll");
        Log::Info("runtime was missing, dll {}", std::bit_cast<uint64_t>(runtimeDll));

        Assert(runtimeDll, "[Amethyst] Failed to find AmethystRuntime.dll, make sure it is loaded before calling this function.");

        using GetContextLoader = AmethystContext*(*)();
        GetContextLoader func = reinterpret_cast<GetContextLoader>(GetProcAddress(runtimeDll, "GetContextInstance"));

        Assert(func != nullptr, "[Amethyst] Failed to find GetContextInstance function in AmethystRuntime.dll");        

        _AmethystContextInstance = func();
        Assert(_AmethystContextInstance, "[Amethyst] Failed to load AmethystContext instance from AmethystRuntime.dll");
    }

    return *_AmethystContextInstance->mSymbolLoader.get();
}

Minecraft* Amethyst::GetMinecraft()
{
    return _AmethystContextInstance->mClientInstance->minecraft;
}

Level* Amethyst::GetLevel()
{
    ClientInstance* ci = _AmethystContextInstance->mClientInstance;
    if (!ci) return nullptr;
    return ci->minecraft->getLevel();
}
