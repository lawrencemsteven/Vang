#pragma once

#include "glm/glm.hpp"

namespace Vang::Voxel {

	typedef glm::ivec3 ChunkCoord;

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

		Blocks getBlock(uint32_t x, uint32_t y, uint32_t z) const;
		Blocks getBlock(const glm::uvec3& coords) const;
		bool getDirty() const;

		void setBlock(const uint32_t x, const uint32_t y, const uint32_t z, const Blocks block);
		void setBlock(const glm::uvec3& coords, const Blocks block);
		void setDirty(const bool dirty);

		const std::vector<uint32_t>& getAllBlocks() const;

	private:
		std::vector<uint32_t> m_blocks{};
		bool m_dirty{true};

		std::size_t convert3DTo1D(const uint32_t x, const uint32_t y, const uint32_t z) const;
	};

}