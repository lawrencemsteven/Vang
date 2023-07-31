#pragma once

namespace Vang {

	template <class T>
	class BlueprintContainer {

	public:
		void addBlueprint(T blueprint);
		T& getBlueprint(uint32_t blueprint_id);
		std::optional<uint32_t> getBlueprintId(const std::string& name);
		bool setBlueprintId(const std::string fullTechnicalName, uint32_t id);

		uint32_t size() const;

	private:
		std::vector<T> m_all_blueprints;
		std::vector<uint32_t> m_id_to_ref;
		std::map<std::string, uint32_t> m_sorted_names_to_ids;

		bool addSortedName(std::string name, uint32_t index);

		struct BinarySearchReturn {
			uint32_t blueprint_id{0};
			bool found{false};
		};
	};


	template <class T>
	inline void BlueprintContainer<T>::addBlueprint(T blueprint) {
		const uint32_t index = m_all_blueprints.size();
		if (!addSortedName(std::move(blueprint.getFullTechnicalName()), index)) {
			return;
		}
		m_all_blueprints.push_back(std::move(blueprint));
		m_id_to_ref.push_back(index);
	}

	template <class T>
	inline T& BlueprintContainer<T>::getBlueprint(uint32_t blueprint_id) {
		if (blueprint_id >= m_id_to_ref.size()) {
			VANG_FATAL("blueprint_id out of range! ID: " + std::to_string(blueprint_id) +
					   ", SIZE: " + std::to_string(m_id_to_ref.size()));
		}
		return m_all_blueprints[m_id_to_ref[blueprint_id]];
	}

	template <class T>
	inline std::optional<uint32_t> BlueprintContainer<T>::getBlueprintId(const std::string& name) {
		const auto blueprintId = m_sorted_names_to_ids.find(name);

		if (blueprintId == m_sorted_names_to_ids.end()) {
			return std::nullopt;
		}
		return blueprintId->second;
	}

	template <class T>
	inline bool BlueprintContainer<T>::setBlueprintId(const std::string fullTechnicalName,
													  uint32_t id) {
		if (id >= size()) {
			VANG_ERROR("Blueprint ID is too large: " + std::to_string(id) +
					   " Max: " + std::to_string(size()));
			return false;
		}

		const auto current_location = m_sorted_names_to_ids.find(fullTechnicalName);
		if (current_location == m_sorted_names_to_ids.end()) {
			VANG_ERROR("Blueprint Is Missing From BlueprintContainer: " + fullTechnicalName);
			return false;
		}

		// Item already has the correct id.
		if (current_location->second == id) {
			return true;
		}

		const auto new_location =
			m_sorted_names_to_ids.find(getBlueprint(id).getFullTechnicalName());

		uint32_t temp			 = current_location->second;
		current_location->second = new_location->second;
		new_location->second	 = temp;

		temp								  = m_id_to_ref[current_location->second];
		m_id_to_ref[current_location->second] = m_id_to_ref[new_location->second];
		m_id_to_ref[new_location->second]	  = temp;

		return true;
	}

	template <class T>
	inline uint32_t BlueprintContainer<T>::size() const {
		return m_all_blueprints.size();
	}

	template <class T>
	inline bool BlueprintContainer<T>::addSortedName(std::string name, uint32_t index) {

		const uint32_t size = m_sorted_names_to_ids.size();

		m_sorted_names_to_ids.emplace(name, index);

		if (size + 1 != m_sorted_names_to_ids.size()) {
			VANG_FATAL("Two identical blueprint names can not exist!" + name);
			return false;
		}
		return true;
	}

}