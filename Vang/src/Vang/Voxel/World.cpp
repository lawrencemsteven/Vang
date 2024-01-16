#include "World.h"

namespace Vang::Voxel {

	glm::ivec3 World::convertWorldPosToChunkCoord(glm::vec3 worldPos) {
		return convertWorldPosToChunkCoord(static_cast<glm::ivec3>(worldPos));
	}
	glm::ivec3 World::convertWorldPosToChunkCoord(glm::ivec3 worldPos) {
		return worldPos / static_cast<glm::ivec3>(chunkSize);
	}

	Chunk& World::loadChunk(const glm::ivec3& chunkPosition) {
		if (chunkAlreadyLoaded(chunkPosition)) {
			return incrementChunk(chunkPosition);
		}

		return initializeChunk(chunkPosition);
	}

	Chunk& World::loadChunk(const int32_t chunkX, const int32_t chunkY, const int32_t chunkZ) {
		return loadChunk(glm::ivec3{chunkX, chunkY, chunkZ});
	}

	void World::unloadChunk(const glm::ivec3& chunkPosition) {
		if (!chunkAlreadyLoaded(chunkPosition)) {
			return;
		}

		decrementChunk(chunkPosition);
	}

	void World::unloadChunk(const int32_t chunkX, const int32_t chunkY, const int32_t chunkZ) {
		return unloadChunk(glm::ivec3{chunkX, chunkY, chunkZ});
	}

	bool World::chunkAlreadyLoaded(const glm::ivec3& chunkPosition) {
		return m_loadedChunks.count(chunkPosition) > 0;
	}

	Chunk& World::incrementChunk(const glm::ivec3& chunkPosition) {
		m_loadedChunks[chunkPosition].first += 1;
		return *m_loadedChunks[chunkPosition].second;
	}

	void World::decrementChunk(const glm::ivec3& chunkPosition) {
		m_loadedChunks[chunkPosition].first -= 1;
		if (m_loadedChunks[chunkPosition].first == 0) {
			m_loadedChunks.erase(chunkPosition);
		}
	}

	Chunk& World::initializeChunk(const glm::ivec3& chunkPosition) {
		m_loadedChunks.emplace(std::make_pair(
			chunkPosition, std::make_pair(1U, std::make_unique<Chunk>(chunkPosition))));
		return *m_loadedChunks[chunkPosition].second;
	}

}