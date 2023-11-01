#pragma once

#include "Vang/Voxel/ChunkLoader.h"

namespace Vang::Voxel {

	class ChunkRenderer {
	public:
		ChunkRenderer()								   = default;
		~ChunkRenderer()							   = default;
		ChunkRenderer(const ChunkRenderer&)			   = delete;
		ChunkRenderer(ChunkRenderer&&)				   = delete;
		ChunkRenderer& operator=(const ChunkRenderer&) = delete;
		ChunkRenderer& operator=(ChunkRenderer&&)	   = delete;

		uint32_t getTotalRenderedChunks() const {
			return m_totalRenderedChunks;
		}

	private:
		uint32_t m_totalRenderedChunks{0};
		std::unique_ptr<ChunkLoader> m_chunkLoader;
	};

}