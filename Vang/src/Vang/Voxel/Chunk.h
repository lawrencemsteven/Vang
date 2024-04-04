#pragma once

#include "glm/glm.hpp"

namespace Vang::Voxel {

	inline const glm::uvec3 chunkSize{64, 64, 64};

	enum class Blocks : uint32_t {
		None,
		Air,
		Fog,
		Black,
		Gray,
		LightGray,
		White,
		Red,
		Orange,
		Yellow,
		Green,
		Blue,
		Purple,
		Pink,
		Rainbow,
	};

	class Chunk {
	public:
		Chunk();
		~Chunk()					   = default;
		Chunk(const Chunk&)			   = delete;
		Chunk(Chunk&&)				   = delete;
		Chunk& operator=(const Chunk&) = delete;
		Chunk& operator=(Chunk&&)	   = delete;

		void setBlock(const uint32_t x, const uint32_t y, const uint32_t z, const Blocks block);
		void setBlock(const glm::uvec3& coords, const Blocks block);
		Blocks getBlock(uint32_t x, uint32_t y, uint32_t z) const;
		Blocks getBlock(const glm::uvec3& coords) const;

		const std::vector<uint32_t>& getAllBlocks() const;

	private:
		std::vector<uint32_t> m_blocks{};

		std::size_t convert3DTo1D(const uint32_t x, const uint32_t y, const uint32_t z) const;
	};

}