#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/actor/ActorFlags.hpp>

class ActorStatusProvider {
public:
	/**@vidx {0}*/
	MC virtual bool getStatusFlag(ActorFlags flag) const = 0;

	/**@vidx {1}*/
	MC virtual void setStatusFlag(ActorFlags flag, bool value) = 0;
};