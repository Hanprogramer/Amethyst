#include "RuntimeContext.hpp"

RuntimeContext::RuntimeContext() { } 

void RuntimeContext::Start()
{
    // Non persistent across mod loads
    mHookManager = std::make_unique<Amethyst::HookManager>();
    mEventBus = std::make_unique<Amethyst::EventBus>();
    mInputManager = std::make_unique<Amethyst::InputManager>(this);
    mPatchManager = std::make_unique<Amethyst::PatchManager>();
    mEnumAllocator = std::make_unique<Amethyst::EnumAllocator>();
    mPackManager = std::make_unique<Amethyst::PackManager>(this);
    mNetworkManager = std::make_unique<Amethyst::NetworkManager>();
    mItemOwnerNameRegistry = std::make_unique<Amethyst::ItemOwnerNameRegistry>();
}

void RuntimeContext::Shutdown()
{
    mHookManager.reset();
    mEventBus.reset();
    mInputManager.reset();
    mPatchManager.reset();
    mEnumAllocator.reset();
    mPackManager.reset();
    mNetworkManager.reset();
    mItemOwnerNameRegistry.reset();
}