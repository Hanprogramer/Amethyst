#pragma once

template <typename C>
class CapabilityRegistry {
private:
	using CapabilityConstructor = std::function<std::unique_ptr<C>(const HashedString& name)>;

	CapabilityConstructor constructor;
	std::unordered_map<HashedString, std::unique_ptr<C>> capabilities;
	std::mutex mutex;
	
public:
	CapabilityRegistry(CapabilityConstructor constructor) : constructor(constructor) {}

	C& create(const HashedString& name) {
        std::lock_guard lock(mutex);

        auto it = capabilities.find(name);
        if (it != capabilities.end()) {
            return *it->second;
        }

        auto obj = constructor(name);
        auto inserted = capabilities.emplace(name, std::move(obj));
        return *inserted.first->second;
    }

	std::vector<C> getAll() const {
        std::vector<C> out;
        out.reserve(capabilities.size());

        for (const auto& entry : capabilities)
            out.push_back(*entry.second);

        return out;
    }
};