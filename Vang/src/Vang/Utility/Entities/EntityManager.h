#pragma once

#include "Entity.h"

namespace Vang::Utility {

	class EntityManager {
	public:
		typedef uint32_t EntityID;

		EntityManager() = default;

		const std::vector<Entity>& getEntities();
		Entity& getEntity(const EntityID entityID);
		const Entity& getEntity(const EntityID entityID) const;

		EntityID createEntity();
		EntityID createEntity(const glm::vec4 position, const float radius);

	private:
		std::vector<Entity> m_entities{};
	};

}