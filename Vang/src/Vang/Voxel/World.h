#pragma once

#include "Chunk.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

namespace Vang::Voxel {

	typedef uint32_t worldID;

	class World {
	public:
		World()						   = default;
		~World()					   = default;
		World(const World&)			   = delete;
		World(World&&)				   = delete;
		World& operator=(const World&) = delete;
		World& operator=(World&&)	   = delete;

		static glm::ivec3 convertWorldPosToChunkCoord(const glm::vec3& worldPos);
		static glm::ivec3 convertWorldPosToChunkCoord(glm::ivec3 worldPos);

		void setBlock(glm::ivec3 worldPos, uint32_t block);

		std::shared_ptr<Chunk> loadChunk(const glm::ivec3& chunkPosition);

	private:
		std::unordered_map<glm::ivec3, std::shared_ptr<Chunk>> m_loadedChunks{};

		std::optional<std::shared_ptr<Chunk>> isChunkLoaded(const glm::ivec3& chunkPosition) const;
		std::shared_ptr<Chunk> initializeChunk(const glm::ivec3& chunkPosition);
	};

}