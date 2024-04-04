#include "EntityManager.h"

namespace Vang::Utility {

	std::vector<Entity>& Vang::Utility::EntityManager::getEntities() {
		m_dirty = true;
		return m_entities;
	}

	const std::vector<Entity>& Vang::Utility::EntityManager::getEntities() const {
		return m_entities;
	}

	Entity& EntityManager::getEntity(const EntityID entityID) {
		return m_entities[entityID];
	}

	const Entity& EntityManager::getEntity(const EntityID entityID) const {
		return m_entities[entityID];
	}

	bool EntityManager::getDirty() {
		return m_dirty;
	}

	EntityManager::EntityID EntityManager::createEntity() {
		m_entities.push_back(Entity{});
		setDirty(true);
		return static_cast<EntityManager::EntityID>(m_entities.size() - 1);
	}

	EntityManager::EntityID EntityManager::createEntity(const glm::vec3 position,
														const float radius) {
		m_entities.push_back(Entity{position, radius});
		setDirty(true);
		return static_cast<EntityManager::EntityID>(m_entities.size() - 1);
	}

	void EntityManager::setDirty(bool dirty) {
		m_dirty = dirty;
	}
}