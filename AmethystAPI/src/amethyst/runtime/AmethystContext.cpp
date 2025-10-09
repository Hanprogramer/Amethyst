#include "AmethystContext.hpp"

AmethystContext::AmethystContext(std::unique_ptr<Amethyst::Platform> platform, std::thread::id amethystThread)
    : mPlatform(std::move(platform)), mAmethystThread(amethystThread) {}