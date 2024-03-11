#pragma once

#include "Entity.h"

namespace Vang::Utility {

	class EntityManager {
	public:
		typedef uint32_t EntityID;

		EntityManager() = default;

		std::vector<Entity>& getEntities();
		const std::vector<Entity>& getEntities() const;
		Entity& getEntity(const EntityID entityID);
		const Entity& getEntity(const EntityID entityID) const;
		bool getDirty();

		EntityID createEntity();
		EntityID createEntity(const glm::vec3 position, const float radius);
		void setDirty(bool dirty);

	private:
		std::vector<Entity> m_entities{};
		bool m_dirty{true};
	};

}