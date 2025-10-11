#pragma once
#include <mc/src/common/gamerefs/gamerefs_shareptr/GameRefsSharePtr.hpp>
#include <cstddef>

template <typename T>
class OwnerPtr : public std::shared_ptr<T> {
public:
    using Base = std::shared_ptr<T>;

    // Inherit all constructors from std::shared_ptr<T>
    using Base::Base;

    constexpr OwnerPtr() noexcept = default;
    constexpr ~OwnerPtr() = default;

    // Converting constructors
    template <class Y>
    constexpr OwnerPtr(const std::shared_ptr<Y>& ptr)
        requires(std::convertible_to<Y*, T*>)
        : Base(ptr)
    {
    }

    template <class Y>
    constexpr OwnerPtr(std::shared_ptr<Y>&& ptr) noexcept
        requires(std::convertible_to<Y*, T*>)
        : Base(std::move(ptr))
    {
    }

    template <class Y>
    constexpr OwnerPtr(const OwnerPtr<Y>& other)
        requires(std::convertible_to<Y*, T*>)
        : Base(other)
    {
    }

    template <class Y>
    constexpr OwnerPtr(OwnerPtr<Y>&& other) noexcept
        requires(std::convertible_to<Y*, T*>)
        : Base(std::move(other))
    {
    }

    // Assignment operators
    template <class Y>
    constexpr OwnerPtr& operator=(const std::shared_ptr<Y>& other)
        requires(std::convertible_to<Y*, T*>)
    {
        Base::operator=(other);
        return *this;
    }

    template <class Y>
    constexpr OwnerPtr& operator=(std::shared_ptr<Y>&& other) noexcept
        requires(std::convertible_to<Y*, T*>)
    {
        Base::operator=(std::move(other));
        return *this;
    }

    template <class Y>
    constexpr OwnerPtr& operator=(const OwnerPtr<Y>& other)
        requires(std::convertible_to<Y*, T*>)
    {
        Base::operator=(other);
        return *this;
    }

    template <class Y>
    constexpr OwnerPtr& operator=(OwnerPtr<Y>&& other) noexcept
        requires(std::convertible_to<Y*, T*>)
    {
        Base::operator=(std::move(other));
        return *this;
    }

    // Optional convenience methods
    constexpr void reset() { Base::reset(); }
    constexpr T* get() const { return Base::get(); }
    constexpr T& operator*() const { return *Base::get(); }
    constexpr T* operator->() const { return Base::get(); }
    constexpr explicit operator bool() const { return static_cast<bool>(*this); }
};