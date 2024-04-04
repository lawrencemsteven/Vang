#pragma once

#include "glm/glm.hpp"

namespace Vang::Utility {

	class Entity {
	public:
		Entity() = default;
		Entity(glm::vec3 position, const float radius);

		const glm::vec3& getPosition() const;
		float getRadius() const;
		bool getDirty() const;

		void setPosition(glm::vec3 position);
		void setRadius(const float radius);
		void setDirty(const bool dirty);

	private:
		glm::vec3 m_position{};
		float m_radius{};
		bool m_dirty{false};
	};

}