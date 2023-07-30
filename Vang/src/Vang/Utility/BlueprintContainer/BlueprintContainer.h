#pragma once

namespace Vang {

	template <class T>
	class BlueprintContainer {

	public:
		void addBlueprint(T blueprint);
		T& getBlueprint(uint32_t blueprint_id);
		std::optional<uint32_t> getBlueprintId(const std::string name);
		bool setBlueprintId(const std::string fullTechnicalName, uint32_t id);

		uint32_t size() const;

	private:
		std::vector<T> all_blueprints;
		std::vector<uint32_t> id_to_ref;
		std::vector<std::pair<std::string, uint32_t>> sorted_names_to_ids;

		bool addSortedName(std::string name, uint32_t index);

		struct BinarySearchReturn {
			uint32_t sorted_location{0};
			uint32_t blueprint_id{0};
			bool found{false};
		};

		inline BinarySearchReturn sortedNamesBinarySearch(const std::string& name) {
			if (sorted_names_to_ids.size() == 0) {
				return {};
			}

			uint32_t start = 0;
			uint32_t end   = sorted_names_to_ids.size();
			uint32_t mid;
			while (start < end) {
				mid							  = ((end - start) / 2) + start;
				const std::string& looking_at = sorted_names_to_ids[mid].first;
				if (name < looking_at) {
					end = mid;
				}
				else if (name > looking_at) {
					start = mid + 1;
				}
				else {
					return {mid, sorted_names_to_ids[mid].second, true};
				}
			}

			return {start, start, false};
		}
	};


	template <class T>
	inline void BlueprintContainer<T>::addBlueprint(T blueprint) {
		const uint32_t index = all_blueprints.size();
		if (!addSortedName(std::move(blueprint.getFullTechnicalName()), index)) {
			return;
		}
		all_blueprints.push_back(std::move(blueprint));
		id_to_ref.push_back(index);
	}

	template <class T>
	inline T& BlueprintContainer<T>::getBlueprint(uint32_t blueprint_id) {
		if (blueprint_id >= id_to_ref.size()) {
			VANG_FATAL("blueprint_id out of range! ID: " + std::to_string(blueprint_id) +
					   ", SIZE: " + std::to_string(id_to_ref.size()));
		}
		return all_blueprints[id_to_ref[blueprint_id]];
	}

	template <class T>
	inline std::optional<uint32_t> BlueprintContainer<T>::getBlueprintId(const std::string name) {
		const auto bin_search = sortedNamesBinarySearch(std::move(name));

		if (bin_search.found) {
			return bin_search.blueprint_id;
		}
		return std::nullopt;
	}

	template <class T>
	inline bool BlueprintContainer<T>::setBlueprintId(const std::string fullTechnicalName,
													  uint32_t id) {
		if (id >= size()) {
			VANG_ERROR("Blueprint ID is too large: " + std::to_string(id) +
					   " Max: " + std::to_string(size()));
			return false;
		}

		const auto current_location = sortedNamesBinarySearch(std::move(fullTechnicalName));
		if (!current_location.found) {
			VANG_ERROR("Blueprint Is Missing From BlueprintContainer!");
			return false;
		}

		// Item already has the correct id.
		if (current_location.blueprint_id == id) {
			return true;
		}

		const auto new_location = sortedNamesBinarySearch(getBlueprint(id).getFullTechnicalName());

		sorted_names_to_ids[current_location.sorted_location].second = new_location.blueprint_id;
		sorted_names_to_ids[new_location.sorted_location].second = current_location.blueprint_id;

		uint32_t temp							 = id_to_ref[current_location.blueprint_id];
		id_to_ref[current_location.blueprint_id] = id_to_ref[new_location.blueprint_id];
		id_to_ref[new_location.blueprint_id]	 = temp;

		return true;
	}

	template <class T>
	inline uint32_t BlueprintContainer<T>::size() const {
		return all_blueprints.size();
	}

	template <class T>
	inline bool BlueprintContainer<T>::addSortedName(std::string name, uint32_t index) {
		const auto bin_search = sortedNamesBinarySearch(name);

		if (bin_search.found) {
			VANG_FATAL("Two identical blueprint names can not exist!" + name);
			return false;
		}

		sorted_names_to_ids.insert(sorted_names_to_ids.begin() + bin_search.sorted_location,
								   {std::move(name), index});
		return true;
	}

}