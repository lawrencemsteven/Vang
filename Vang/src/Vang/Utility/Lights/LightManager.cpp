#include "LightManager.h"

namespace Vang::Utility {

	const std::vector<Light>& Vang::Utility::LightManager::getLights() const {
		return m_lights;
	}

	Light& LightManager::getLight(const LightID LightID) {
		return m_lights[LightID];
	}

	bool LightManager::getDirty() {
		return m_dirty;
	}

	LightManager::LightID LightManager::createLight() {
		m_lights.push_back(Light{});
		setDirty(true);
		return static_cast<LightManager::LightID>(m_lights.size() - 1);
	}

	LightManager::LightID LightManager::createLight(const glm::vec3 position, const glm::vec3 color,
													const float radius, const float intensity) {
		m_lights.push_back(Light{position, color, radius, intensity});
		setDirty(true);
		return static_cast<LightManager::LightID>(m_lights.size() - 1);
	}

	void LightManager::setDirty(bool dirty) {
		m_dirty = dirty;
	}

	void LightManager::cleanLight(const std::size_t lightIdx) {
		m_lights[lightIdx].setDirty(false);
	}
}