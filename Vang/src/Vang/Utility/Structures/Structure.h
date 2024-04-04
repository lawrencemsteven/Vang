#pragma once

#include "Vang/Voxel/Chunk.h"

namespace Vang::Utility::Structure {

	void generateStructure(int32_t xOffset, int32_t zOffset, int32_t length, int32_t width,
						   int32_t height, Vang::Voxel::Blocks liveBlock,
						   Vang::Voxel::Blocks deadBlock);

}