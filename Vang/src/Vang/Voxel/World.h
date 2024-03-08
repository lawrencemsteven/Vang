#pragma once

#include "Chunk.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

namespace Vang::Voxel {

	typedef uint32_t worldID;

	class World {
	public:
		World();
		~World()					   = default;
		World(const World&)			   = delete;
		World(World&&)				   = delete;
		World& operator=(const World&) = delete;
		World& operator=(World&&)	   = delete;

		static glm::ivec3 convertWorldPosToChunkCoord(glm::ivec3 worldPos);
		static glm::ivec3 convertWorldPosToChunkCoord(const int32_t x, const int32_t y,
													  const int32_t z);
		static glm::ivec3 convertWorldPosToChunkCoord(const glm::vec3& worldPos);
		static glm::ivec3 convertWorldPosToChunkCoord(const float x, const float y, const float z);

		void setBlock(const int32_t x, const int32_t y, const int32_t z, const Blocks block);
		void setBlock(glm::ivec3 worldPos, const Blocks block);

		Blocks getBlock(const int32_t x, const int32_t y, const int32_t z);
		bool getSolid(const int32_t x, const int32_t y, const int32_t z);

		std::shared_ptr<Chunk> loadChunk(const glm::ivec3& chunkPosition);

	private:
		std::unordered_map<glm::ivec3, std::shared_ptr<Chunk>> m_loadedChunks{};

		std::optional<std::shared_ptr<Chunk>> isChunkLoaded(const glm::ivec3& chunkPosition) const;
		std::shared_ptr<Chunk> initializeChunk(const glm::ivec3& chunkPosition);
	};

}