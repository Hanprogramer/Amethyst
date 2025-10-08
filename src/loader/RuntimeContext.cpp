#include "loader/RuntimeContext.hpp"

RuntimeContext::RuntimeContext(std::unique_ptr<Amethyst::Platform> platform)
    : AmethystContext(std::move(platform)) {}

void RuntimeContext::Start()
{
    mHookManager = std::make_unique<Amethyst::HookManager>();
    mEventBus = std::make_unique<Amethyst::EventBus>();
    mInputManager = std::make_unique<Amethyst::InputManager>(this);
    mPatchManager = std::make_unique<Amethyst::PatchManager>();
    mEnumAllocator = std::make_unique<Amethyst::EnumAllocator>();
    mPackManager = std::make_unique<Amethyst::PackManager>(this);
    mNetworkManager = std::make_unique<Amethyst::NetworkManager>();
    mModRepository = std::make_unique<Amethyst::ModRepository>();
    mModGraph = std::make_unique<Amethyst::ModGraph>();
    mModLoader = std::make_unique<Amethyst::ModLoader>(this);
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
    mModRepository.reset();
    mModGraph.reset();
    mModLoader.reset();
}