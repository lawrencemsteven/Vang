#pragma once

#include "ChunkLoader.h"

namespace Vang::Voxel {

	class CubeChunkLoader : public ChunkLoader {
	public:
		CubeChunkLoader(const glm::ivec3& centerPosition, const uint32_t width);
		~CubeChunkLoader() = default;

		glm::ivec3 getCenterPosition() const;
		void setCenterPosition(glm::ivec3 centerPosition);
		uint32_t getWidth() const;
		void setWidth(const uint32_t width);

	private:
		uint32_t m_width{0U};
		glm::ivec3 m_centerPosition{0,0,0};

		void updateChunks();
	};

}