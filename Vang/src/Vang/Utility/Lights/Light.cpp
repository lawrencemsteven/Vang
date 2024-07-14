#include "Light.h"

namespace Vang::Utility {
	Light::Light(glm::vec3 position, glm::vec3 color, const float radius, const float intensity)
		: m_position{std::move(position)},
		  m_color{std::move(color)},
		  m_radius{radius},
		  m_intensity{intensity} {}

	const glm::vec3& Light::getPosition() const {
		return m_position;
	}

	const glm::vec3& Light::getColor() const {
		return m_color;
	}

	float Light::getRadius() const {
		return m_radius;
	}

	float Light::getIntensity() const {
		return m_intensity;
	}

	bool Light::getDirty() const {
		return m_dirty;
	}

	void Light::setPosition(glm::vec3 position) {
		setDirty(true);
		m_position = std::move(position);
	}

	void Light::setColor(glm::vec3 color) {
		setDirty(true);
		m_color = std::move(color);
	}

	void Light::setRadius(const float radius) {
		setDirty(true);
		m_radius = radius;
	}

	void Light::setIntensity(const float intensity) {
		setDirty(true);
		m_intensity = std::move(intensity);
	}

	void Light::setDirty(const bool dirty) {
		m_dirty = dirty;
	}
}