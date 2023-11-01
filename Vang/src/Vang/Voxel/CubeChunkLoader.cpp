#include "CubeChunkLoader.h"

namespace Vang::Voxel {

	CubeChunkLoader::CubeChunkLoader(const glm::ivec3& centerPosition, const uint32_t width) {
		setWidth(width);
	}
	glm::ivec3 CubeChunkLoader::getCenterPosition() const {
		return m_centerPosition;
	}
	void CubeChunkLoader::setCenterPosition(glm::ivec3 centerPosition) {
		m_centerPosition = std::move(centerPosition);
		updateChunks();
	}
	uint32_t CubeChunkLoader::getWidth() const {
		return m_width;
	}
	void CubeChunkLoader::setWidth(const uint32_t width) {
		m_width = width;
		updateChunks();
	}

	void CubeChunkLoader::updateChunks() {
		VANG_ERROR("Functionality not yet implemented!");
	}

}