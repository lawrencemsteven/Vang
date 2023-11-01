#include "ChunkLoader.h"

#include "Vang.h"

namespace Vang::Voxel {

	ChunkLoader::ChunkLoader() {
		m_chunkLoaderId = Vang::detail::addChunkLoader(*this);
	}

	ChunkLoader::~ChunkLoader() {
		Vang::detail::removeChunkLoader(m_chunkLoaderId);
	}

	void ChunkLoader::update() {
		for (auto chunk : m_chunks) {
			chunk.get().update();
		}
	}

	uint32_t ChunkLoader::getTotalLoadedChunks() const {
		return m_totalLoadedChunks;
	}

}