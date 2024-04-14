#pragma once
#include "glm/glm.hpp"

#include "Vang/Voxel/World.h"

namespace Vang::VMath {
	struct raycastReturn {
		bool hit{false};
		Vang::Voxel::Blocks blockHit{Vang::Voxel::Blocks::Air};
		glm::ivec3 blockHitPosition{0, 0, 0};
		glm::ivec3 newBlockVector{0, 0, 0};
		float distance{0.0f};
	};

	const raycastReturn raycast(Vang::Voxel::World& world, glm::vec3 rayOrigin,
								const glm::vec3& rayDirection, float maxDistance);
}