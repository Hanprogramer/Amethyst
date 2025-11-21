#pragma once
#include <mc/src-deps/core/string/StringHash.hpp>

class BaseCapability {
private:
	HashedString name;

protected:
	BaseCapability(const HashedString& name) : name(name) {}

public:
	const HashedString& getName() const {
		return name;
	}
};