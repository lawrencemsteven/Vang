#pragma once

#include "glm/glm.hpp"

namespace Vang::Voxel::Rendering {

	class ChunkRenderer {
	public:
		ChunkRenderer()	 = default;
		~ChunkRenderer() = default;

		uint32_t getRenderDistance() const;

		void setRenderDistance(uint32_t renderDistance);

	private:
		uint32_t m_renderDistance{};
	};

}