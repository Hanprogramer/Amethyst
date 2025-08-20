#pragma once
#include <amethyst/Memory.hpp>
class Player;
class BlockPos;

class BlockEventCoordinator {
public:
    void sendBlockInteractedWith(Player& player, const BlockPos& pos) {
        using function = decltype(&BlockEventCoordinator::sendBlockInteractedWith);
        static auto func = std::bit_cast<function>(SigScan("48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4C 8B B1 ? ? ? ? 48 8B FA"));
        return (this->*func)(player, pos);
    }
};