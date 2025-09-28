#include <mc/src/common/dataloadhelper/DefaultDataLoadHelper.hpp>

DefaultDataLoadHelper::DefaultDataLoadHelper()
{
    this->vtable = (uintptr_t**)SlideAddress(0x4D79138);
}
