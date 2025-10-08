#include "AmethystContext.hpp"

AmethystContext::AmethystContext(std::unique_ptr<Amethyst::Platform> platform)
    : mPlatform(std::move(platform)) {}