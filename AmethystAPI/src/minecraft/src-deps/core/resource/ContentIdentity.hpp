#pragma once
#include <minecraft/src-deps/core/utility/UUID.hpp>

class ContentIdentity {
public:
    mce::UUID mUUID;
    bool mValid;

    const ContentIdentity& operator=(const ContentIdentity& other) {
        mUUID = other.mUUID;
        mValid = other.mValid;
        return *this;
    }
};