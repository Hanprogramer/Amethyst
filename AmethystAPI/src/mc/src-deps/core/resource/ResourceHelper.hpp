#pragma once
#include "mc/src-deps/core/resource/ResourceUtil.hpp"
#include <string>
#include "mc/src-deps/core/semVer/SemVersion.hpp"
#include "mc/src-deps/core/utility/UUID.hpp"

enum class PackCategory : int {
    _Unknown,
    _RealmsUnknown,
    Standard,
    Premium,
    Custom,
    Subpack
};

enum class PackType : char {
    Invalid,
    Addon,
    Cached,
    CopyProtected,
    Behavior,
    PersonaPiece,
    Resources,
    Skins,
    WorldTemplate,
    Count
};

enum class PackOrigin : char {
    _Unknown,
    _RealmsUnknown,
    Package,
    Treatment,
    Dev,
    World,
    User,
    TempCache,
    PremiumCache,
    PremiumTempCache
};

struct PackIdVersion {
    mce::UUID mId;
    SemVersion mVersion;
    PackType mPackType;
};

class ResourceLocation {
public:
    ResourceFileSystem mFileSystem; // this + 0x0
    std::string mPath;              // this + 0x8
    uint64_t mPathHash;             // this + 0x28
    uint64_t mFullHash;             // this + 0x30

public:
    ~ResourceLocation();
    ResourceLocation();
    ResourceLocation(const std::string& path);
    ResourceLocation(const char* path);

private:
    void _computeHashes();
};

static_assert(offsetof(ResourceLocation, mPath) == 8);