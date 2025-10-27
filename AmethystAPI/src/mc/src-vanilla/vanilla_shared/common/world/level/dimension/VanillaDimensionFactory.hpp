/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/util/Factory.hpp>

class ILevel;
class Scheduler;
class Dimension;

namespace VanillaDimensionFactory {
    /// @address {0x40818E0}
    MC void registerDimensionTypes(OwnerPtrFactory<Dimension, ILevel&, Scheduler&>& factory);
};