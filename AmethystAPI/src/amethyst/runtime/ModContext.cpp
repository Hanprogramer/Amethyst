#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/MinecraftVtables.hpp>
#include <minecraft/src/common/Minecraft.hpp>

static AmethystContext* _AmethystContextInstance;
static std::unique_ptr<Amethyst::ModInfo> _ModInfo;

void Amethyst::InitializeAmethystMod(AmethystContext& context, std::unique_ptr<ModInfo> info)
{
    // Initialize vtbl pointers & ctor pointers.
    InitializeVtablePtrs();

    // Store a persistent AmethystContext instance
    _AmethystContextInstance = &context;

    // Store mod info
    _ModInfo = std::move(info);
}

const Amethyst::ModInfo* Amethyst::GetOwnModInfo()
{
    return _ModInfo.get();
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

Amethyst::NetworkManager& Amethyst::GetNetworkManager()
{
    return *_AmethystContextInstance->mNetworkManager.get();
}

Minecraft* Amethyst::GetMinecraft()
{
    return _AmethystContextInstance->mClientInstance->mMinecraft;
}

Level* Amethyst::GetLevel()
{
    ClientInstance* ci = _AmethystContextInstance->mClientInstance;
    if (!ci) return nullptr;
    return ci->mMinecraft->getLevel();
}

ClientInstance* Amethyst::GetClientInstance()
{
    return _AmethystContextInstance->mClientInstance;
}
