#include "World.h"

namespace Vang::Voxel {

	glm::ivec3 World::convertWorldPosToChunkCoord(const glm::vec3& worldPos) {
		return convertWorldPosToChunkCoord(static_cast<glm::ivec3>(worldPos));
	}
	glm::ivec3 World::convertWorldPosToChunkCoord(glm::ivec3 worldPos) {
		return worldPos / static_cast<glm::ivec3>(chunkSize);
	}

	void World::setBlock(glm::ivec3 worldPos, uint32_t block) {
		const auto chunkPos = convertWorldPosToChunkCoord(worldPos);

		const auto chunk = loadChunk(chunkPos);

		chunk->setBlock(worldPos - chunkPos, block);
	}

	std::shared_ptr<Chunk> World::loadChunk(const glm::ivec3& chunkPosition) {
		const auto chunkOptional = isChunkLoaded(chunkPosition);

		return chunkOptional.value_or(initializeChunk(chunkPosition));
	}

	std::optional<std::shared_ptr<Chunk>>
	World::isChunkLoaded(const glm::ivec3& chunkPosition) const {
		auto chunkSearch = m_loadedChunks.find(chunkPosition);

		if (chunkSearch != m_loadedChunks.end()) {
			return chunkSearch->second;
		}

		return std::nullopt;
	}

	std::shared_ptr<Chunk> World::initializeChunk(const glm::ivec3& chunkPosition) {
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();

		m_loadedChunks[chunkPosition] = chunk;
		return chunk;
	}

}