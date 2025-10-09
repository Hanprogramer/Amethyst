#include "AmethystContext.hpp"

AmethystContext::AmethystContext(std::unique_ptr<Amethyst::Platform> platform, std::thread::id amethystThread) : 
    mPlatform(std::move(platform)), 
    mAmethystThread(amethystThread), 
    mClientCtx(std::make_unique<Amethyst::ClientContext>()), 
    mServerCtx(nullptr) {}