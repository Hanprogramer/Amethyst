#pragma once
#include <stdint.h> // for uintptr_t for $vtable_for_this definitions

#define MC __declspec(dllimport) 

using UnknownReturn = void; // placeholder for unknown return types