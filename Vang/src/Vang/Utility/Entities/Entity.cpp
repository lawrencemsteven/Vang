#include "Entity.h"

namespace Vang::Utility {
	Entity::Entity(glm::vec3 position, const float radius)
		: m_position{std::move(position)},
		  m_radius{radius} {}

	const glm::vec3& Entity::getPosition() const {
		return m_position;
	}

	float Entity::getRadius() const {
		return m_radius;
	}

	bool Entity::getDirty() const {
		return m_dirty;
	}

	void Entity::setPosition(glm::vec3 position) {
		m_position = std::move(position);
	}

	void Entity::setRadius(const float radius) {
		m_radius = radius;
	}

	void Entity::setDirty(const bool dirty) {
		m_dirty = dirty;
	}
}