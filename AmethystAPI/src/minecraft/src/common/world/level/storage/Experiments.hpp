#pragma once
#include <minecraft/src/common/world/level/storage/ExperimentsStorage.hpp>

class Experiments : public ExperimentsStorage {
public:
    Experiments() : ExperimentsStorage() {}
    Experiments(const ExperimentsStorage& other) : ExperimentsStorage(other) {}
};