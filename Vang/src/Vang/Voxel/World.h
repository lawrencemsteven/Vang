#pragma once

#include "Chunk.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

namespace Vang::Voxel {

	class World {
	public:
		static glm::ivec3 convertWorldPosToChunkCoord(glm::vec3 worldPos);
		static glm::ivec3 convertWorldPosToChunkCoord(glm::ivec3 worldPos);

		Chunk& loadChunk(const glm::ivec3& chunkPosition);
		Chunk& loadChunk(const int32_t chunkX, const int32_t chunkY, const int32_t chunkZ);
		void unloadChunk(const glm::ivec3& chunkPosition);
		void unloadChunk(const int32_t chunkX, const int32_t chunkY, const int32_t chunkZ);

	private:
		std::unordered_map<glm::ivec3, std::pair<uint32_t, std::unique_ptr<Chunk>>> m_loadedChunks;

		bool chunkAlreadyLoaded(const glm::ivec3& chunkPosition);
		Chunk& incrementChunk(const glm::ivec3& chunkPosition);
		void decrementChunk(const glm::ivec3& chunkPosition);
		Chunk& initializeChunk(const glm::ivec3& chunkPosition);
	};

}