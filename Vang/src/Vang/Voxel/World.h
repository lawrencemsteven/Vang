#pragma once

#include "Chunk.h"

namespace Vang::Voxel {

	class World {
	public:
		World();

	private:
		std::vector<Chunk> m_loadedChunks;
	};

}