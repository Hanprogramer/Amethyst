#pragma once
#include <memory>
#include <cstddef>

template <typename T>
class OwnerStorageSharePtr {
public:
    std::shared_ptr<T> mValue;

	T* get() const {
        return mValue.get();
    }

protected:
    bool _hasValue() const;
    void _reset();

    std::shared_ptr<T> _getShared() const {
        return mValue;
    }

    T& _getStackRef() const {
        return *mValue.get();
    }
};