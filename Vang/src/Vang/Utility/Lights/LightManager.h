#pragma once

#include "Light.h"

namespace Vang::Utility {

	class LightManager {
	public:
		typedef uint32_t LightID;

		LightManager()										 = default;
		~LightManager()										 = default;
		LightManager(const LightManager& i_copy)			 = delete;
		LightManager& operator=(const LightManager& i_other) = delete;
		LightManager(LightManager&& i_copy)					 = delete;
		LightManager& operator=(LightManager&& i_other)		 = delete;

		const std::vector<Light>& getLights() const;
		Light& getLight(const LightID LightID);
		bool getDirty();

		LightID createLight();
		LightID createLight(const glm::vec3 position, const glm::vec3 color, const float radius,
							const float intensity);
		void setDirty(bool dirty);
		void cleanLight(const std::size_t lightIdx);

	private:
		std::vector<Light> m_lights{};
		bool m_dirty{true};
	};

}