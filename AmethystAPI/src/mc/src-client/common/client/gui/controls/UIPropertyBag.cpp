#include "UIPropertyBag.hpp"

UIPropertyBag::UIPropertyBag() {}

UIPropertyBag::UIPropertyBag(const Json::Value& value)
    : PropertyBag(value) {}
