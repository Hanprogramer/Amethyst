#include "C:\Users\blake\Documents\Modding\Mods\Amethyst-Playground\build\.gens\AmethystAPI\windows\x64\release\__\__\Amethyst\AmethystAPI\src\amethyst\Imports.hpp"
#include "Material.hpp"

Material& Material::getMaterial(MaterialType type)
{
    // Seems to fall back to dirt if its out of range
    if ((uint32_t)type > mMaterials.size()) {
        type = MaterialType::Dirt;
        Log::Warning("Material::getMaterial called with MaterialType {}, which is out of range for mMaterials", (uint32_t)type);
    }

    return *mMaterials.at((uint32_t)type).get();
}
