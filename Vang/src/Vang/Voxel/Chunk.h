#pragma once

#include "glm/glm.hpp"

namespace Vang::Voxel {

	inline const glm::uvec3 chunkSize{16, 16, 16};

	class Chunk {
	public:
		Chunk();
		Chunk(const glm::ivec3& chunkPosition);
		Chunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ);
		Chunk(const Chunk&)						 = delete;
		Chunk(Chunk&&)							 = delete;
		Chunk& operator=(const Chunk&)			 = default;
		Chunk& operator=(Chunk&&)				 = default;

		void setBlock(uint32_t x, uint32_t y, uint32_t z, uint32_t block);
		void setBlock(const glm::uvec3& coords, uint32_t block);
		uint32_t getBlock(uint32_t x, uint32_t y, uint32_t z) const;
		uint32_t getBlock(const glm::uvec3& coords) const;

		void update();

	private:
		glm::ivec3 m_chunkPosition{};
		std::array<uint32_t, 4096> m_blocks{};

		void generateChunk();
	};

}