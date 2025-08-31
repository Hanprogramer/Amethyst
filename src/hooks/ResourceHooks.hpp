#pragma once
#include <string>
#include "AmethystRuntime.hpp"
#include "amethyst/runtime/HookManager.hpp"

class IResourcePackRepository;
class ResourcePackStack;

namespace lambda {
// The lambda capture structure used in initializeResourceStack
struct Pack {
    Bedrock::NonOwnerPointer<IResourcePackRepository> repo;
    ResourcePackStack& stack;

    void addFromUUID(const PackIdVersion& version)
    {
        using function = decltype(&lambda::Pack::addFromUUID);
        static auto func = std::bit_cast<function>(*SigScanSafe("48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B D9 48 8B 09"));
        (this->*func)(version);
    }
};
} // namespace lambda

void CreateResourceHooks();