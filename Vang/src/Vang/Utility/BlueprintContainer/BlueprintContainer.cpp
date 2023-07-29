#include "BlueprintContainer.h"

namespace Vang {

    template <class T>
	void Vang::BlueprintContainer<T>::addBlueprint(T blueprint) {
		all_blueprints.push_back(std::move(blueprint));
		const uint32_t index = all_blueprints.size() - 1;
		id_to_ref.push_back(0, all_blueprints[index]);
		addSortedName(std::move(blueprint.getFullTechnicalName()), index);
	}

	template <class T>
	std::optional<T&> BlueprintContainer<T>::getBlueprint(uint32_t blueprint_id) {
		if (blueprint_id < id_to_ref.size()) {
			return id_to_ref[blueprint_id];
		}
		return std::nullopt_t;
	}

	template <class T>
	std::optional<T&> BlueprintContainer<T>::getBlueprint(std::string name) {
		const auto bin_search = sortedNamesBinarySearch(std::move(name));

		if (bin_search[1]) {
			return id_to_ref[bin_search[0]];
		}
		return std::nullopt_t;
	}

	template <class T>
	std::optional<uint32_t> BlueprintContainer<T>::getBlueprintId(std::string name) {
		const auto bin_search = sortedNamesBinarySearch(name);
		if (bin_search[1]) {
			return bin_search[0];
		}
		return std::nullopt_t;
	}

	template <class T>
	void BlueprintContainer<T>::addSortedName(std::string name, uint32_t index) {
		const auto bin_search = sortedNamesBinarySearch(name);

		if (bin_search[1]) {
			VANG_FATAL("Two identical blueprint names can not exist!" + name);
			return;
		}
		
		const auto pair_to_add = std::pair<std::string, uint32_t>(std::move(name), index);
		
		sorted_names_to_ids.insert(std::move(pair_to_add), bin_search[0]);
	}

	template <class T>
	std::pair<uint32_t, bool> BlueprintContainer<T>::sortedNamesBinarySearch(const std::string& name) {
		if (sorted_names_to_ids.size() == 0) {
			return std::pair<uint32_t, bool>{0, false};
		}

		uint32_t start = 0;
		uint32_t end   = sorted_names_to_ids.size();
		uint32_t mid;
		while (start < end) {
			mid							  = (end - start) / 2;
			const std::string& looking_at = sorted_names_to_ids[mid][0];
			if (name < looking_at) {
				end = mid;
			}
			else if (name > looking_at) {
				start = mid;
			}
			else {
				return std::pair<uint32_t, bool>{mid, true};
			}
		}

		return std::pair<uint32_t, bool>{start, false};
	}
    
}