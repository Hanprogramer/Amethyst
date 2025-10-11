#include "AmethystContext.hpp"

AmethystContext::AmethystContext(std::unique_ptr<Amethyst::Platform> platform, std::thread::id amethystThread) : 
    mAmethystAbiHash(AmethystContext::GetAmethystAbiHash()),
    mPlatform(std::move(platform)), 
    mAmethystThread(amethystThread), 
    mClientCtx(std::make_unique<Amethyst::ClientContext>()), 
    mServerCtx(nullptr) {}

uint64_t AmethystContext::GetAmethystAbiHash()
{
    std::string abiDescription;

    abiDescription += "sizeof(AmethystContext):" + std::to_string(sizeof(AmethystContext));
    abiDescription += "offsetof(mPlatform):" + std::to_string(offsetof(AmethystContext, mPlatform));
    abiDescription += "offsetof(mHookManager):" + std::to_string(offsetof(AmethystContext, mHookManager));
    abiDescription += "sizeof(Amethyst::SharedContext):" + std::to_string(sizeof(Amethyst::SharedContext));
    abiDescription += "sizeof(Amethyst::ClientContext):" + std::to_string(sizeof(Amethyst::ClientContext));
    abiDescription += "sizeof(Amethyst::ServerContext):" + std::to_string(sizeof(Amethyst::ServerContext));

    return HashedString::computeHash(abiDescription);
}
