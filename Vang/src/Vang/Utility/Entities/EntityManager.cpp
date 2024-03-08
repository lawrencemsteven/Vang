#include "EntityManager.h"

namespace Vang::Utility {

	const std::vector<Entity>& Vang::Utility::EntityManager::getEntities() {
		return m_entities;
	}

	Entity& EntityManager::getEntity(const EntityID entityID) {
		return m_entities[entityID];
	}

	const Entity& EntityManager::getEntity(const EntityID entityID) const {
		return m_entities[entityID];
	}

	EntityManager::EntityID EntityManager::createEntity() {
		m_entities.push_back(Entity{});
		return m_entities.size() - 1;
	}

	EntityManager::EntityID EntityManager::createEntity(const glm::vec4 position,
														const float radius) {
		m_entities.push_back(Entity{position, radius});
		return m_entities.size() - 1;
	}
}