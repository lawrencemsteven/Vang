#pragma once

namespace Vang {

    template<class T>
    class BlueprintContainer {
	public:
		void addBlueprint(T blueprint);
		std::optional<T&> getBlueprint(uint32_t blueprint_id);
		std::optional<T&> getBlueprint(std::string name);
		std::optional<uint32_t> getBlueprintId(std::string name);

    private:
		std::vector<T> all_blueprints;
		std::vector<T&> id_to_ref;
		std::vector<std::pair<std::string, uint32_t>> sorted_names_to_ids;

		void addSortedName(std::string name, uint32_t index);
		
		// The bool represents whether the exact name was found or not
		std::pair<uint32_t, bool> sortedNamesBinarySearch(const std::string& name);
    };

}