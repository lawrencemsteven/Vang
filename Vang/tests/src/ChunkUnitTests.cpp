#include <catch2/catch_test_macros.hpp>

#include "Vang/Voxel/Chunk.h"

TEST_CASE("Vang::Voxel::Chunk") {
	SECTION("Cuboids") {
		SECTION("Empty Cuboid") {
			Vang::Voxel::Chunk chunk{};

			const auto& blocks = chunk.getAllBlocks();

			CHECK(blocks[1] == 1041204192);
		}
		SECTION("Flat Ground") {
			Vang::Voxel::Chunk chunk{};

			for (uint32_t x = 0; x < Vang::Voxel::CHUNK_SIZE.x; x++) {
				for (uint32_t z = 0; z < Vang::Voxel::CHUNK_SIZE.z; z++) {
					chunk.setBlock(x, 0, z, Vang::Voxel::Blocks::Green);
				}
			}
			chunk.setBlock(10, 10, 10, Vang::Voxel::Blocks::Green);
			chunk.greedyCuboidCompilation();

			const auto& blocks = chunk.getAllBlocks();

			CHECK(chunk.getCuboid(0, 1, 0) == 1041171424);
		}
	}
}