#pragma once

#include "glm/glm.hpp"

namespace Vang::Voxel {

	inline const glm::uvec3 chunkSize{64, 64, 64};

	class Chunk {
	public:
		Chunk()						   = default;
		~Chunk()					   = default;
		Chunk(const Chunk&)			   = delete;
		Chunk(Chunk&&)				   = delete;
		Chunk& operator=(const Chunk&) = delete;
		Chunk& operator=(Chunk&&)	   = delete;

		void setBlock(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t block);
		void setBlock(const glm::uvec3& coords, const uint32_t block);
		uint32_t getBlock(uint32_t x, uint32_t y, uint32_t z) const;
		uint32_t getBlock(const glm::uvec3& coords) const;

		const std::vector<uint32_t>& getAllBlocks() const;

	private:
		std::vector<uint32_t> m_blocks{chunkSize[0] * chunkSize[1] * chunkSize[2]};

		std::size_t convert3DTo1D(const uint32_t x, const uint32_t y, const uint32_t z) const;
	};

}