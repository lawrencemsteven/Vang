#pragma once

#include "Vang/Voxel/Chunk.h"

namespace Vang::Voxel {

	class ChunkLoader {
	public:
		ChunkLoader()							   = default;
		~ChunkLoader()							   = default;
		ChunkLoader(const ChunkLoader&)			   = delete;
		ChunkLoader(ChunkLoader&&)				   = delete;
		ChunkLoader& operator=(const ChunkLoader&) = delete;
		ChunkLoader& operator=(ChunkLoader&&)	   = delete;

		virtual void update() = 0;

		uint32_t getTotalLoadedChunks() const;

	private:
		uint32_t m_totalLoadedChunks{0};
		std::vector<std::reference_wrapper<Chunk>> m_chunks;
	};

}