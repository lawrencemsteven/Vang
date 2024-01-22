#include "Chunk.h"

namespace Vang::Voxel {

	void Chunk::setBlock(const uint32_t x, const uint32_t y, const uint32_t z,
						 const uint32_t block) {
		const auto loc = convert3DTo1D(x, y, z);

		m_blocks[loc] = block;
	}

	void Chunk::setBlock(const glm::uvec3& coords, const uint32_t block) {
		setBlock(coords[0], coords[1], coords[2], block);
	}

	uint32_t Chunk::getBlock(uint32_t x, uint32_t y, uint32_t z) const {
		const auto loc = convert3DTo1D(x, y, z);

		return m_blocks[loc];
	}

	uint32_t Chunk::getBlock(const glm::uvec3& coords) const {
		return getBlock(coords[0], coords[1], coords[2]);
	}

	const std::vector<uint32_t>& Chunk::getAllBlocks() const {
		return m_blocks;
	}

	std::size_t Chunk::convert3DTo1D(const uint32_t x, const uint32_t y, const uint32_t z) const {
		return x + (chunkSize[2] * z) + (chunkSize[1] * chunkSize[1] * y);
	}

}