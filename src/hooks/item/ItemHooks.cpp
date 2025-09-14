#include "hooks/item/ItemHooks.hpp"
#include "AmethystRuntime.hpp"
#include <amethyst/runtime/HookManager.hpp>
#include <amethyst/runtime/AmethystContext.hpp>
#include <minecraft/src/common/world/item/ItemStack.hpp>
#include <minecraft/src/common/world/level/Level.hpp>


SafetyHookInline _Item_appendFormattedHovertext;
void Item_appendFormattedHovertext(const Item* self, const ItemStackBase& stack, Level& level, std::string& hovertext, bool showCategory)
{
    _Item_appendFormattedHovertext.thiscall<
        void,
        const Item*,
        const ItemStackBase&,
        Level&,
        std::string&,
        bool>(self, stack, level, hovertext, showCategory);

    std::string_view fullName = self->mFullName.getString();
    std::string_view modNameView = fullName.substr(0, fullName.find(':'));

    std::string modName;
    if (modNameView.empty() || modNameView == "minecraft") {
        modName = "Minecraft";
    }
    else {
        modName.reserve(modNameView.size());
        bool cap = true;
        for (char c : modNameView) {
            if (c == '_') {
                modName.push_back(' ');
                cap = true;
            }
            else if (cap) {
                modName.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
                cap = false;
            }
            else {
                modName.push_back(c);
            }
        }
    }

    hovertext += "\n§o§9" + modName + "§r";
}

void CreateItemHooks()
{
    Amethyst::HookManager& hooks = *AmethystRuntime::getHookManager();
    VHOOK(Item, appendFormattedHovertext, this);
}