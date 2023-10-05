#pragma once

#include "Chunk.h"

namespace Vang::Voxel {

	class World {
	public:

		static glm::ivec3 convertWorldPosToChunkCoord(glm::vec3 worldPos);

	private:
		std::vector<Chunk> m_loadedChunks;
	};

}