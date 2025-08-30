#pragma once
#include <amethyst/Memory.hpp>
class Player;
class BlockPos;

class BlockEventCoordinator {
public:
    // inlined on client
    /*void sendBlockInteractedWith(Player& player, const BlockPos& pos) {
        using function = decltype(&BlockEventCoordinator::sendBlockInteractedWith);
        static auto func = std::bit_cast<function>(SigScan("")); 
        return (this->*func)(player, pos);
    }*/
};