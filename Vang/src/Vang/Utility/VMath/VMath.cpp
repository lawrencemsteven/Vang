#include "VMath.h"

namespace Vang::VMath {
	float planeIntersectionDistance(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
									const glm::vec3& planeOrigin, const glm::vec3& planeNormal) {
		const float denom = glm::dot(planeNormal, rayDirection);
		if (abs(denom) > 0.0f) {
			const glm::vec3 pointDist = planeOrigin - rayOrigin;
			float dist				  = glm::dot(pointDist, planeNormal) / denom;
			return dist;
		}
		// Large enough for a miss
		// Might never be reached???
		return 100.0f;
	}

	const raycastReturn Vang::VMath::raycast(Vang::Voxel::World& world, glm::vec3 rayOrigin,
											 const glm::vec3& rayDirection, float maxDistance) {
		raycastReturn output{};

		// TODO: Cleanup

		glm::ivec3 currentBlockPos = Vang::Voxel::World::convertWorldPosToBlockCoord(rayOrigin);
		while (output.distance <= maxDistance) {
			glm::vec3 signedDirection = glm::sign(rayDirection);

			glm::ivec3 distDir = glm::ivec3{round(signedDirection.x), 0, 0};
			float minDist =
				planeIntersectionDistance(rayOrigin, rayDirection,
										  glm::vec3(currentBlockPos.x + 0.5f * signedDirection.x,
													currentBlockPos.y, currentBlockPos.z),
										  glm::vec3(-glm::sign(rayDirection.x), 0.0f, 0.0f));

			float newDist = planeIntersectionDistance(
				rayOrigin, rayDirection,
				glm::vec3(currentBlockPos.x, currentBlockPos.y + 0.5f * signedDirection.y,
						  currentBlockPos.z),
				glm::vec3(0.0f, -glm::sign(rayDirection.y), 0.0f));
			if (newDist < minDist) {
				distDir = glm::ivec3(0, round(signedDirection.y), 0);
				minDist = newDist;
			}

			newDist =
				planeIntersectionDistance(rayOrigin, rayDirection,
										  glm::vec3(currentBlockPos.x, currentBlockPos.y,
													currentBlockPos.z + 0.5f * signedDirection.z),
										  glm::vec3(0.0f, 0.0f, -glm::sign(rayDirection.z)));
			if (newDist < minDist) {
				distDir = glm::ivec3(0, 0, round(signedDirection.z));
				minDist = newDist;
			}

			currentBlockPos += distDir;
			const auto currentBlock = world.getBlock(currentBlockPos);
			rayOrigin += rayDirection * minDist;
			output.distance += minDist;
			if (currentBlock != Vang::Voxel::Blocks::Air &&
				currentBlock != Vang::Voxel::Blocks::Fog) {
				output.hit				= true;
				output.blockHit			= currentBlock;
				output.blockHitPosition = currentBlockPos;
				output.newBlockVector	= distDir;
				return output;
			}
		}

		output.distance = maxDistance;

		return output;
	}
}
