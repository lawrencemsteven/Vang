#pragma once

#include "Chunk.h"

namespace Vang {

	class World {
	public:
		World();

	private:
		std::vector<Chunk> m_loadedChunks;
	};

}