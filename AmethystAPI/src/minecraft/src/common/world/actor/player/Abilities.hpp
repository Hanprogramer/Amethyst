#pragma once
#include <array>

enum class CommandPermissionLevel : __int8
{
  Any = 0x0,
  GameDirectors = 0x1,
  Admin = 0x2,
  Host = 0x3,
  Owner = 0x4,
  Internal = 0x5,
};

class PermissionsHandler
{
  CommandPermissionLevel mCommandPermissions;
  unsigned char mPlayerPermissions[1];
};

class Ability {
  enum class Type : unsigned char {Invalid, Unset, Bool, Float};
  enum class Options : unsigned char {None, NoSave, CommandExposed, PermissionsInterfaceExposed = 4};

  union Value {
    bool mBoolVal;
    float mFloatVal;
  };

  Type mType;
  Value mValue;
  Options mOptions;
};

class Abilities {
  std::array<Ability,19> mAbilities;
};

const class LayeredAbilities {
  PermissionsHandler mPermissions;
  std::array<Abilities,5> mLayers;
};