#include "World.h"

namespace Vang::Voxel {

	glm::ivec3 World::convertWorldPosToChunkCoord(glm::vec3 worldPos) {
		return static_cast<glm::ivec3>(worldPos) / static_cast<glm::ivec3>(chunkSize);
	}

}