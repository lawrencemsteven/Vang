#include "ChunkRenderer.h"
#include "Vang.h"

namespace Vang::Voxel::Rendering {

	ChunkRenderer::ChunkRenderer(const uint32_t renderDistance) {
		setRenderDistance(renderDistance);
	}

	uint32_t Vang::Voxel::Rendering::ChunkRenderer::getRenderDistance() const {
		return m_renderDistance;
	}

	uint32_t ChunkRenderer::getRenderDiameter() const {
		return m_renderDistance * 2 + 1;
	}

	const std::vector<std::shared_ptr<Chunk>>& ChunkRenderer::getChunks() const {
		return m_chunks;
	}

	bool ChunkRenderer::getDirty() const {
		return m_dirty;
	}

	void ChunkRenderer::setRenderDistance(const uint32_t renderDistance) {
		setDirty(true);
		m_renderDistance = renderDistance;
		updateChunks();
	}

	void ChunkRenderer::setCenter(const ChunkCoord& centerChunk) {
		if (m_centerChunk == centerChunk) {
			return;
		}

		setDirty(true);
		m_centerChunk = centerChunk;
		updateChunks();
	}

	void ChunkRenderer::setCenter(const glm::vec3& position) {
		const ChunkCoord chunkCoord = World::convertWorldPosToChunkCoord(position);

		setCenter(chunkCoord);
	}

	void ChunkRenderer::setDirty(const bool dirty) {
		m_dirty = dirty;
	}

	void ChunkRenderer::updateChunks() {
		const uint32_t renderDiameter = getRenderDiameter();
		const uint32_t chunksSize	  = renderDiameter * renderDiameter * renderDiameter;
		if (m_chunks.size() != chunksSize) {
			m_chunks.resize(chunksSize);
		}

		uint32_t chunkCounter = 0;
		for (uint32_t x = 0; x < renderDiameter; x++) {
			for (uint32_t y = 0; y < renderDiameter; y++) {
				for (uint32_t z = 0; z < renderDiameter; z++) {
					const auto chunk	   = Vang::getCurrentWorld().loadChunk({x, y, z});
					m_chunks[chunkCounter] = chunk;
					chunkCounter += 1;
				}
			}
		}
	}
}