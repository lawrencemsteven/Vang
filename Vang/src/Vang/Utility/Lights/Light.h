#pragma once

#include "glm/glm.hpp"

namespace Vang::Utility {

	class Light {
	public:
		Light() = default;
		Light(glm::vec3 position, glm::vec3 color, const float radius, const float intensity);

		const glm::vec3& getPosition() const;
		const glm::vec3& getColor() const;
		float getRadius() const;
		float getIntensity() const;
		bool getDirty() const;

		void setPosition(glm::vec3 position);
		void setColor(glm::vec3 color);
		void setRadius(const float radius);
		void setIntensity(const float intensity);
		void setDirty(const bool dirty);

	private:
		glm::vec3 m_position{};
		glm::vec3 m_color{};
		float m_radius{};
		float m_intensity{};
		bool m_dirty{false};
	};

}