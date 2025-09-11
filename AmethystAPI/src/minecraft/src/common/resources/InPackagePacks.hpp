/// @symbolgeneration
#pragma once
#include "minecraft/src-deps/core/file/Path.hpp"
#include "minecraft/src-deps/core/resource/ResourceHelper.hpp"
#include <amethyst/ModApi.hpp>

/// @vptr {0x4EBAA28, this}
MC class IInPackagePacks
{
public:
    struct MetaData {
    public:
        Core::PathBuffer<std::string> mPath;
        bool mIsHidden;
        PackCategory mPackCategory;

        MetaData(const Core::Path& path, const bool isHidden, PackCategory packCategory) {
            mPath.mContainer = path.mPathPart.mUtf8StdString;
            mIsHidden = isHidden;
            mPackCategory = packCategory;
        }
    };

    /// @vidx {0, this}
    MC virtual ~IInPackagePacks() = 0;
    /// @vidx {1, this}
    MC virtual std::vector<IInPackagePacks::MetaData> getPacks(PackType packType) const = 0;
};