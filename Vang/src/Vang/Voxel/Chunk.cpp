#include "Chunk.h"

namespace Vang::Voxel {

	Chunk::Chunk() {
		m_blocks.resize(chunkSize[0] * chunkSize[1] * chunkSize[2]);
		std::fill(m_blocks.begin(), m_blocks.end(), static_cast<uint32_t>(Blocks::Air));
	}

	void Chunk::setBlock(const uint32_t x, const uint32_t y, const uint32_t z, const Blocks block) {
		const auto loc = convert3DTo1D(x, y, z);

		m_blocks[loc] = static_cast<uint32_t>(block);
	}

	void Chunk::setBlock(const glm::uvec3& coords, const Blocks block) {
		setBlock(coords[0], coords[1], coords[2], block);
	}

	void Chunk::setDirty(const bool dirty) {
		m_dirty = dirty;
	}

	Blocks Chunk::getBlock(uint32_t x, uint32_t y, uint32_t z) const {
		const auto loc = convert3DTo1D(x, y, z);

		return static_cast<Blocks>(m_blocks[loc]);
	}

	Blocks Chunk::getBlock(const glm::uvec3& coords) const {
		return getBlock(coords[0], coords[1], coords[2]);
	}

	bool Chunk::getDirty() const {
		return m_dirty;
	}

	const std::vector<uint32_t>& Chunk::getAllBlocks() const {
		return m_blocks;
	}

	std::size_t Chunk::convert3DTo1D(const uint32_t x, const uint32_t y, const uint32_t z) const {
		return x + (chunkSize[2] * z) + (chunkSize[1] * chunkSize[1] * y);
	}

}