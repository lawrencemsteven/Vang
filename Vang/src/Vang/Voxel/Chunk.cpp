#include "Chunk.h"

namespace Vang::Voxel {

	Chunk::Chunk() {
		m_blocks.resize(CHUNK_SIZE[0] * CHUNK_SIZE[1] * CHUNK_SIZE[2] * 2);
		generateChunk();
		resetCuboids();
	}

	void Chunk::setBlock(const uint32_t x, const uint32_t y, const uint32_t z, const Blocks block) {
		const auto loc = convert3DTo1D(x, y, z);

		setDirty(true);
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

	void Chunk::greedyCuboidCompilation() {
		// TODO: Multi-thread this
		resetCuboids();

		// Iterate over each block
		for (uint32_t x = 0; x < CHUNK_SIZE[0]; x++) {
			for (uint32_t z = 0; z < CHUNK_SIZE[2]; z++) {
				for (uint32_t y = CHUNK_SIZE[1] - 1; y < CHUNK_SIZE[1]; y--) {
					if (!isCuboid(x, y, z)) {
						calcCuboid(x, y, z);
					}
				}
			}
		}
	}

	bool Chunk::getDirty() const {
		return m_dirty;
	}

	const std::vector<uint32_t>& Chunk::getAllBlocks() const {
		return m_blocks;
	}

	std::size_t Chunk::convert3DTo1D(const uint32_t x, const uint32_t y, const uint32_t z) const {
		return x + (CHUNK_SIZE[2] * z) + (CHUNK_SIZE[1] * CHUNK_SIZE[1] * y);
	}

	std::size_t Chunk::convert3DTo1DCuboid(const uint32_t x, const uint32_t y,
										   const uint32_t z) const {
		return x + (CHUNK_SIZE[2] * z) + (CHUNK_SIZE[1] * CHUNK_SIZE[1] * y) + BLOCK_COUNT;
	}

	uint32_t Chunk::getCuboid(const uint32_t x, const uint32_t y, const uint32_t z) {
		return m_blocks[convert3DTo1DCuboid(x, y, z)];
	}

	void Chunk::generateChunk() {
		std::fill(m_blocks.begin(), m_blocks.begin() + BLOCK_COUNT,
				  static_cast<uint32_t>(Blocks::Air));
	}

	void Chunk::resetCuboids() {
		std::fill(m_blocks.begin() + BLOCK_COUNT, m_blocks.end(), 0u);
	}

	bool Chunk::isCuboid(const uint32_t x, const uint32_t y, const uint32_t z) {
		return getCuboid(x, y, z) << 2 > 0;
	}

	void Chunk::setCuboidDirection(const uint32_t x, const uint32_t y, const uint32_t z,
								   const CuboidDirection dir, const uint32_t val) {
		m_blocks[convert3DTo1DCuboid(x, y, z)] |= val << static_cast<uint8_t>(dir);
	}

	// TODO: Requires all values in startPos <= endPos
	bool Chunk::checkCuboidEquality(const glm::uvec3& startPos, const glm::uvec3& endPos,
									const Blocks block) {
		for (uint32_t x = startPos.x; x <= endPos.x; x++) {
			for (uint32_t y = startPos.y; y <= endPos.y; y++) {
				for (uint32_t z = startPos.z; z <= endPos.z; z++) {
					if (getBlock(x, y, z) != block) {
						return false;
					}
				}
			}
		}
		return true;
	}

	void Chunk::calcCuboid(const uint32_t x, const uint32_t y, const uint32_t z) {
		bool incrementX = true;
		bool decrementY = true;
		bool incrementZ = true;

		glm::uvec3 cuboidSize{0, 0, 0};

		Blocks block = getBlock(x, y, z);

		// TODO: Non-transparent blocks should not be cuboided
		// TODO: Cleanup
		while (incrementX || decrementY || incrementZ) {
			if (incrementX) {
				if (x + cuboidSize.x + 1 > CHUNK_SIZE.x) {
					incrementX = false;
				}
				if (checkCuboidEquality({x, y - cuboidSize.y, z},
										{x + cuboidSize.x + 1, y, z + cuboidSize.z}, block)) {
					cuboidSize.x += 1;
				}
				else {
					incrementX = false;
				}
			}

			if (decrementY) {
				if (y - cuboidSize.y - 1 > CHUNK_SIZE.y) {
					decrementY = false;
				}
				else if (checkCuboidEquality({x, y - cuboidSize.y - 1, z},
											 {x + cuboidSize.x, y, z + cuboidSize.z}, block)) {
					cuboidSize.y += 1;
				}
				else {
					decrementY = false;
				}
			}

			if (incrementZ) {
				if (z + cuboidSize.z + 1 > CHUNK_SIZE.z) {
					incrementZ = false;
				}
				if (checkCuboidEquality({x, y - cuboidSize.y, z},
										{x + cuboidSize.x, y, z + cuboidSize.z + 1}, block)) {
					cuboidSize.z += 1;
				}
				else {
					incrementZ = false;
				}
			}
		}

		if (cuboidSize == glm::uvec3{0, 0, 0}) {
			return;
		}

		for (uint32_t x = 0; x < cuboidSize.x + 1; x++) {
			for (uint32_t y = 0; y < cuboidSize.y + 1; y++) {
				for (uint32_t z = 0; z < cuboidSize.z + 1; z++) {
					setCuboidDirection(x, y, z, CuboidDirection::PositiveX, cuboidSize.x - x);
					setCuboidDirection(x, y, z, CuboidDirection::NegativeX, x);
					setCuboidDirection(x, y, z, CuboidDirection::PositiveY, cuboidSize.y - y);
					setCuboidDirection(x, y, z, CuboidDirection::NegativeY, y);
					setCuboidDirection(x, y, z, CuboidDirection::PositiveZ, cuboidSize.z - z);
					setCuboidDirection(x, y, z, CuboidDirection::NegativeZ, z);
				}
			}
		}
	}
}