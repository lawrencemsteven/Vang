#pragma once

#include "Vang/Voxel/World.h"

namespace Vang::Voxel {

	class ChunkLoader {
	public:
		ChunkLoader();
		~ChunkLoader();
		ChunkLoader(const ChunkLoader&)			   = delete;
		ChunkLoader(ChunkLoader&&)				   = delete;
		ChunkLoader& operator=(const ChunkLoader&) = delete;
		ChunkLoader& operator=(ChunkLoader&&)	   = delete;

		void update();

		uint32_t getTotalLoadedChunks() const;

	protected:
		uint32_t m_totalLoadedChunks{0U};
		std::vector<std::reference_wrapper<Chunk>> m_chunks;

	private:
		uint32_t m_chunkLoaderId{};
	};

}