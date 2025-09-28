#pragma once
#include <mc/src/common/gamerefs/gamerefs_shareptr/OwnerStorageSharePtr.hpp>

template <typename T>
struct SharePtrRefTraits {
    typedef T StackRef;
    typedef OwnerStorageSharePtr<T> OwnerStorage;
    typedef SharePtrRefTraits<T>::StackRef OwnerStackRef;
};