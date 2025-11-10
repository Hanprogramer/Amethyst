/// @symbols
#pragma once
#include <mc/src/common/world/effect/MobEffect.hpp>
#include <mc/src/common/world/effect/EffectDuration.hpp>

class MobEffectInstance {
public:
	unsigned int mId;
	EffectDuration mDuration;
	std::optional<EffectDuration> mDurationEasy;
	std::optional<EffectDuration> mDurationNormal;
	std::optional<EffectDuration> mDurationHard;
	int mAmplifier;
	bool mDisplayOnScreenTextureAnimation;
	bool mAmbient;
	bool mNoCounter;
	bool mEffectVisible;

public:
	/// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B F2 4C 8B E1 48 89 54 24}
	MC std::string getDisplayName() const;
};