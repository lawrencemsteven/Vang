#pragma once

#include "glm/glm.hpp"

namespace Vang::Voxel {

	typedef glm::ivec3 ChunkCoord;

	inline const glm::uvec3 CHUNK_SIZE{64, 64, 64};
	const uint32_t BLOCK_COUNT = CHUNK_SIZE[0] * CHUNK_SIZE[1] * CHUNK_SIZE[2];

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
		Glass,
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

		void greedyCuboidCompilation();

		const std::vector<uint32_t>& getAllBlocks() const;

	private:
		std::vector<uint32_t> m_blocks{};
		bool m_dirty{true};

		std::size_t convert3DTo1D(const uint32_t x, const uint32_t y, const uint32_t z) const;
		std::size_t convert3DTo1DCuboid(const uint32_t x, const uint32_t y, const uint32_t z) const;




		/////////////
		// Cuboids //
		/////////////
		//
		// 00 00000 00000 00000 00000 00000 00000
		//  1   2     3     4     5     6     7
		//
		// Todo: First bit should be transparency
		//
		// 1 = Block Information
		//
		// 2 = +X
		// 3 = -X
		//
		// 4 = +Y
		// 5 = -Y
		//
		// 6 = +Z
		// 7 = -Z
		//

		enum class CuboidDirection {
			PositiveX = 25,
			NegativeX = 20,
			PositiveY = 15,
			NegativeY = 10,
			PositiveZ = 5,
			NegativeZ = 0,
		};

		uint32_t getCuboid(const uint32_t x, const uint32_t y, const uint32_t z);
		void generateChunk();
		void resetCuboids();
		bool isCuboid(const uint32_t x, const uint32_t y, const uint32_t z);
		void setCuboidDirection(const uint32_t x, const uint32_t y, const uint32_t z,
								const CuboidDirection dir, const uint32_t val);
		bool checkCuboidEquality(const glm::uvec3& startPos, const glm::uvec3& endPos,
								 const Blocks block);
		void calcCuboid(const uint32_t x, const uint32_t y, const uint32_t z);
	};

}