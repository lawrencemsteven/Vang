#include "World.h"

namespace Vang::Voxel {

	ChunkCoord World::convertWorldPosToChunkCoord(glm::ivec3 worldPos) {
		return worldPos / static_cast<glm::ivec3>(CHUNK_SIZE);
	}

	ChunkCoord World::convertWorldPosToChunkCoord(const int32_t x, const int32_t y,
												  const int32_t z) {
		return convertWorldPosToChunkCoord(glm::ivec3{x, y, z});
	}

	ChunkCoord World::convertWorldPosToChunkCoord(const glm::vec3& worldPos) {
		return convertWorldPosToChunkCoord(static_cast<glm::ivec3>(worldPos));
	}

	ChunkCoord World::convertWorldPosToChunkCoord(const float x, const float y, const float z) {
		const int32_t newX = static_cast<int32_t>(x);
		const int32_t newY = static_cast<int32_t>(y);
		const int32_t newZ = static_cast<int32_t>(z);
		return convertWorldPosToChunkCoord(glm::ivec3{newX, newY, newZ});
	}

	glm::ivec3 World::convertWorldPosToBlockCoord(const glm::vec3& worldPos) {
		return glm::round(worldPos);
	}

	glm::ivec3 World::convertWorldPosToBlockCoord(const float x, const float y, const float z) {
		return convertWorldPosToBlockCoord({x, y, z});
	}

	void World::setBlock(const int32_t x, const int32_t y, const int32_t z, const Blocks block) {
		const auto chunkPos = convertWorldPosToChunkCoord(x, y, z);

		const auto chunk = loadChunk(chunkPos);

		chunk->setBlock(x - chunkPos.x, y - chunkPos.y, z - chunkPos.z, block);
	}

	void World::setBlock(glm::ivec3 worldPos, Blocks block) {
		const auto chunkPos = convertWorldPosToChunkCoord(worldPos);

		const auto chunk = loadChunk(chunkPos);

		chunk->setBlock(worldPos - chunkPos * glm::ivec3{CHUNK_SIZE}, block);
	}
	Blocks World::getBlock(const int32_t x, const int32_t y, const int32_t z) {
		// TODO: Remove world boundaries
		if (x > 576 || x < 0 || y > 576 || y < 0 || z > 576 || z < 0) {
			return Blocks::None;
		}

		const auto chunkPos = convertWorldPosToChunkCoord(x, y, z);

		const auto chunk = loadChunk(chunkPos);

		return chunk->getBlock(x - chunkPos.x * CHUNK_SIZE.x, y - chunkPos.y * CHUNK_SIZE.y,
							   z - chunkPos.z * CHUNK_SIZE.z);
	}

	Blocks World::getBlock(const glm::ivec3& pos) {
		return getBlock(pos.x, pos.y, pos.z);
	}

	bool World::getSolid(const int32_t x, const int32_t y, const int32_t z) {
		return getBlock(x, y, z) < Blocks::Black;
	}

	std::shared_ptr<Chunk> World::loadChunk(const glm::ivec3& chunkPosition) {
		const auto chunkOptional = isChunkLoaded(chunkPosition);

		if (chunkOptional.has_value()) {
			return chunkOptional.value();
		}

		return initializeChunk(chunkPosition);
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