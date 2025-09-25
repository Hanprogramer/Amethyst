#include "amethyst/runtime/mod/ModGraph.hpp"
#include <unordered_set>
#include <functional>

namespace Amethyst {
void ModGraph::Clear() {
	mMods.clear();
	mErrors.clear();
}

void ModGraph::SortAndValidate(const ModRepository& repository, const std::vector<std::string>& launcherMods) {
    Clear();
    const ModInfoMap& repoMods = repository.GetMods();

    std::unordered_set<const ModInfo*> visited;
    std::unordered_set<const ModInfo*> visiting;
    std::vector<const ModInfo*> stack;

    // Helper to push a ModError
    auto pushError = [&](
        const ModInfo* info, 
        ModErrorType type, 
        const std::string& message,
        std::unordered_map<std::string, std::string> data) 
    {
        mErrors.push_back(ModError{
            ModErrorStep::Resolving,
            type,
            info->UUID,
            message,
            std::move(data)
        });
    };

    std::function<bool(const ModInfo*)> visit = [&](const ModInfo* info) -> bool {
        if (visited.contains(info)) return true;

        if (visiting.contains(info)) {
            // Detected a cycle
            std::string cycle;
            for (const auto* modInStack : stack) {
                cycle += modInStack->GetVersionedName() + " -> ";
            }
            cycle += info->GetVersionedName();

            pushError(
                info, 
                ModErrorType::CircularDependency,
                "Cyclic dependency detected: {cycle}",
                {
                    { "{cycle}", cycle }
                }
            );

            return false;
        }

        visiting.insert(info);
        StackGuard<const ModInfo*> guard(stack, info); // RAII push/pop
        bool success = true;

        // Visit dependencies
        for (const auto& dep : info->Dependencies) {
            const ModInfo* found = nullptr;

            // Find matching mod in repo
            for (const auto& [uuid, mod] : repoMods) {
                if (mod.Namespace == dep.Namespace && dep.MatchesMod(mod, false)) {
                    found = &mod;
                    // Check version
                    if (!dep.MatchesVersion(mod.Version)) {
                        if (!dep.IsSoft) {
                            pushError(
                                info,
                                ModErrorType::WrongDependencyVersion,
                                "Mod '{mod}' requires '{dep}' version '{ver}' or higher, but found version '{found_ver}'",
                                {
                                    { "{mod}", info->GetVersionedName() },
                                    { "{dep}", dep.Namespace },
                                    { "{ver}", dep.MinVersion.to_string() },
                                    { "{found_ver}", mod.Version.to_string() }
                                }
                            );
                            success = false;
                        }
                        break;
                    }

                    // Recurse into the dependency
                    if (!visit(&mod)) success = false;
                    break; // Found the dependency
                }
            }

            // If no matching mod found and dependency is required
            if (!found && !dep.IsSoft) {
                pushError(
                    info, 
                    ModErrorType::MissingDependency,
                    "Mod '{mod}' requires '{dep}', but it was not found",
                    {
                        { "{mod}", info->GetVersionedName() },
                        { "{dep}", dep.GetDependencyIdentification() }
                    }
                );
                success = false;
            }
        }

        visiting.erase(info);
        visited.insert(info);
        if (success) {
            mMods.emplace_back(*info);
        }
        return success;
    };

    // Visit all launcher mods
    for (const std::string& modVerName : launcherMods) {
        for (const auto& [uuid, mod] : repoMods) {
            if (mod.GetVersionedName() == modVerName) {
                visit(&mod);
                break;
            }
        }
    }

    //std::reverse(mMods.begin(), mMods.end());
}

const std::vector<ModInfo>& ModGraph::GetMods() const {
    return mMods;
}

const std::vector<ModError>& ModGraph::GetErrors() const {
    return mErrors;
}

bool ModGraph::HasErrors() const {
    return !mErrors.empty();
}

size_t ModGraph::GetModCount() const {
    return mMods.size();
}
} // namespace Amethyst