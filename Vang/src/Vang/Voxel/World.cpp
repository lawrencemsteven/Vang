#include "World.h"

namespace Vang::Voxel {

	World::World() {
		// // TODO: Make world bigger than 256x64x256
		for (std::size_t x = 0; x < 4; x++) {
			for (std::size_t z = 0; z < 4; z++) {
				loadChunk({x, 0, z});
			}
		}

		for (std::size_t x = 0; x < 256; x++) {
			for (std::size_t z = 0; z < 256; z++) {
				setBlock({x, 0, z}, Blocks::Green);
			}
		}
	}

	glm::ivec3 World::convertWorldPosToChunkCoord(glm::ivec3 worldPos) {
		return worldPos / static_cast<glm::ivec3>(chunkSize);
	}

	glm::ivec3 World::convertWorldPosToChunkCoord(const int32_t x, const int32_t y,
												  const int32_t z) {
		return convertWorldPosToChunkCoord(glm::ivec3{x, y, z});
	}

	glm::ivec3 World::convertWorldPosToChunkCoord(const glm::vec3& worldPos) {
		return convertWorldPosToChunkCoord(static_cast<glm::ivec3>(worldPos));
	}

	glm::ivec3 World::convertWorldPosToChunkCoord(const float x, const float y, const float z) {
		const int32_t newX = static_cast<int32_t>(x);
		const int32_t newY = static_cast<int32_t>(y);
		const int32_t newZ = static_cast<int32_t>(z);
		return convertWorldPosToChunkCoord(glm::ivec3{newX, newY, newZ});
	}

	void World::setBlock(const int32_t x, const int32_t y, const int32_t z, const Blocks block) {
		const auto chunkPos = convertWorldPosToChunkCoord(x, y, z);

		const auto chunk = loadChunk(chunkPos);

		chunk->setBlock(x - chunkPos.x, y - chunkPos.y, z - chunkPos.z, block);

		setDirty(true);
	}

	void World::setBlock(glm::ivec3 worldPos, Blocks block) {
		const auto chunkPos = convertWorldPosToChunkCoord(worldPos);

		const auto chunk = loadChunk(chunkPos);

		chunk->setBlock(worldPos - chunkPos * glm::ivec3{chunkSize}, block);

		setDirty(true);
	}

	void World::setDirty(const bool dirty) {
		m_dirty = dirty;
	}

	Blocks World::getBlock(const int32_t x, const int32_t y, const int32_t z) {
		const auto chunkPos = convertWorldPosToChunkCoord(x, y, z);

		const auto chunk = loadChunk(chunkPos);

		return chunk->getBlock(x - chunkPos.x, y - chunkPos.y, z - chunkPos.z);
	}

	bool World::getSolid(const int32_t x, const int32_t y, const int32_t z) {
		return getBlock(x, y, z) < Blocks::Black;
	}

	bool World::getDirty() const {
		return m_dirty;
	}

	std::shared_ptr<Chunk> World::loadChunk(const glm::ivec3& chunkPosition) {
		const auto chunkOptional = isChunkLoaded(chunkPosition);

		if (chunkOptional.has_value()) {
			return chunkOptional.value();
		}

		setDirty(true);

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

		setDirty(true);
		return chunk;
	}

}