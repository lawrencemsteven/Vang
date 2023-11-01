#include "Chunk.h"

namespace Vang::Voxel {

	Chunk::Chunk(const glm::ivec3& chunkPosition)
		: m_chunkPosition{chunkPosition},
		  m_blocks{} {}

	Chunk::Chunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ)
		: Chunk{glm::ivec3{chunkX, chunkY, chunkZ}} {}

	void Chunk::update() {
		// TODO: HANDLE BLOCK INTERACTIONS
	}

	void Chunk::generateChunk() {
		srand((unsigned)time(NULL));

		int random{};
		for (std::size_t i = 0; i < m_blocks.size(); i++) {
			random = rand() % 100;
			if (random < 30) {
				m_blocks[i] = 1;
			}
			else {
				m_blocks[i] = 0;
			}
		}
	}

}