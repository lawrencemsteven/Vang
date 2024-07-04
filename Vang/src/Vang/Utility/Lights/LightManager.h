#pragma once

#include "Light.h"

namespace Vang::Utility {

	class LightManager {
	public:
		typedef uint32_t LightID;

		LightManager() = default;

		std::vector<Light>& getLights();
		const std::vector<Light>& getLights() const;
		Light& getLight(const LightID LightID);
		const Light& getLight(const LightID LightID) const;
		bool getDirty();

		LightID createLight();
		LightID createLight(const glm::vec3 position, const glm::vec3 color, const float radius,
							const float intensity);
		void setDirty(bool dirty);

	private:
		std::vector<Light> m_lights{};
		bool m_dirty{true};
	};

}