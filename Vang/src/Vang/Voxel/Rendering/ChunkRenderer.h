#pragma once

#include "Vang/Voxel/World.h"
#include "glm/glm.hpp"

namespace Vang::Voxel::Rendering {

	class ChunkRenderer {
	public:
		// TODO: Center Chunk Position
		ChunkRenderer(const uint32_t renderDistance);
		~ChunkRenderer() = default;

		uint32_t getRenderDistance() const;
		uint32_t getRenderDiameter() const;
		const std::vector<std::shared_ptr<Chunk>>& getChunks() const;
		bool getDirty() const;

		void setRenderDistance(const uint32_t renderDistance);
		void setCenter(const ChunkCoord& centerChunk);
		void setCenter(const glm::vec3& position);
		void setDirty(const bool dirty);

	private:
		ChunkCoord m_centerChunk{};
		uint32_t m_renderDistance{};
		std::vector<std::shared_ptr<Chunk>> m_chunks{};
		bool m_dirty{false};

		void updateChunks();
	};

}