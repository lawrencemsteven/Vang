#include "Entity.h"

namespace Vang::Utility {
	Entity::Entity(glm::vec4 position, const float radius)
		: m_position{std::move(position)},
		  m_radius{radius} {}

	const glm::vec4& Entity::getPosition() const {
		return m_position;
	}

	float Entity::getRadius() const {
		return m_radius;
	}

	void Entity::setPosition(glm::vec4 position) {
		m_position = std::move(position);
	}

	void Entity::setRadius(const float radius) {
		m_radius = radius;
	}
}