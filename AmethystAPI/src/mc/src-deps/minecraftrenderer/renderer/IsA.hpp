#pragma once

namespace mce {

template<typename EnumType, EnumType Value, typename Underlying>
class IsA {
public:
    static constexpr EnumType ImplementedType = Value;

    static constexpr EnumType getActualType() {
        return ImplementedType;
    }
};

} // namespace mce