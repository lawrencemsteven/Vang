#pragma once

#include "glm/glm.hpp"

namespace Vang::Voxel {

	inline const glm::uvec3 chunkSize{16, 16, 16};

	class Chunk {
	public:
		Chunk(int32_t x, int32_t y, int32_t z);

		void setBlock(uint32_t x, uint32_t y, uint32_t z);

		uint32_t getBlock(uint32_t x, uint32_t y, uint32_t z) const;

	private:
		std::array<uint32_t, 4096> m_blocks;
	};

}