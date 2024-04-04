#include "Structure.h"

#include "Vang.h"

namespace Vang::Utility::Structure {

	int convert2Dto1D(int x, int y, int width) {
		return x + y * width;
	}

	glm::ivec2 convert1Dto2D(const int index, const int width) {
		return glm::ivec2{index % width, index / width};
	}

	bool inGrid(int height, int width, int x, int y) {
		if (x < 0) {
			return false;
		}
		else if (x > width - 1) {
			return false;
		}
		else if (y < 0) {
			return false;
		}
		else if (y > height - 1) {
			return false;
		}
		return true;
	}

	int livingNeighbors(std::vector<int>& dungeon, int height, int width, int x, int y) {
		int living = 0;
		int loopX  = x - 1;
		int loopY  = y - 1;
		while (loopX <= (x + 1)) {
			while (loopY <= (y + 1)) {
				if (!inGrid(height, width, loopX, loopY)) {
					living += 0;
				}
				else {
					living += dungeon[convert2Dto1D(loopX, loopY, width)];
				}
				loopY++;
			}
			loopY = y - 1;
			loopX++;
		}
		return living;
	}

	void firstPass(std::vector<int>& dungeon, int height, int width, int lifeRate) {
		int i = 0;
		int j = 0;
		while (i < height) {
			while (j < width) {
				if ((rand() % 100) < lifeRate) {
					// this is walls
					dungeon[convert2Dto1D(i, j, width)] = 1;
				}
				else {
					// this is blank space
					dungeon[convert2Dto1D(i, j, width)] = 0;
				}
				j++;
			}
			j = 0;
			i++;
		}
	}

	void cellValueUpdate(std::vector<int>& dungeon, std::vector<int>& reference, int x, int y,
						 int birthT, int surviveT, int height, int width) {
		int aliveNeighbors = livingNeighbors(reference, height, width, x, y);
		if (dungeon[convert2Dto1D(x, y, width)] != 1) {
			if (aliveNeighbors >= birthT) {
				dungeon[convert2Dto1D(x, y, width)] = 1;
			}
		}
		else {
			if (!(aliveNeighbors >= surviveT)) {
				dungeon[convert2Dto1D(x, y, width)] = 0;
			}
		}
	}

	void iteration(std::vector<int>& dungeon, std::vector<int>& reference, int height, int width,
				   int birthT, int surviveT) {
		int i = 0;
		int j = 0;
		while (i < height) {
			while (j < width) {
				cellValueUpdate(dungeon, reference, i, j, birthT, surviveT, height, width);
				j++;
			}
			j = 0;
			i++;
		}
	}

	void runStep(std::vector<int>& dungeon, int height, int width, int birthT, int surviveT,
				 int iterations) {
		int i = 0;
		while (i < iterations) {
			std::vector<int> reference{dungeon};
			iteration(dungeon, reference, height, width, birthT, surviveT);
			i++;
		}
	}

	std::vector<int> makeDungeon(int height, int width, int lifeRate, int iterations, int birthT,
								 int surviveT) {
		std::vector<int> output{};
		output.resize(width * height);
		firstPass(output, height, width, lifeRate);
		runStep(output, height, width, birthT, surviveT, iterations);
		return output;
	}

	void placeColumn(Vang::Voxel::World& world, const int32_t x, const int32_t z,
					 const int32_t height, const Vang::Voxel::Blocks block) {
		int32_t y = 1;

		if (block == Vang::Voxel::Blocks::Air) {
			world.setBlock({x, y, z}, Vang::Voxel::Blocks::Fog);
			world.setBlock({x, y + 1, z}, Vang::Voxel::Blocks::Fog);
			y += 2;
		}

		while (y < height) {
			world.setBlock({x, y, z}, block);
			y++;
		}
	}

	void generateStructure(int32_t xOffset, int32_t zOffset, int32_t length, int32_t width,
						   int32_t height, Vang::Voxel::Blocks liveBlock,
						   Vang::Voxel::Blocks deadBlock) {
		// int height = 180;
		// int width  = 180;
		// lifeRate is percent chance representation
		int lifeRate   = 45;
		int iterations = 8;
		int birthT	   = 5;
		int surviveT   = 4;
		std::vector<int> output{makeDungeon(length, width, lifeRate, iterations, birthT, surviveT)};

		auto& world = Vang::getCurrentWorld();



		for (int32_t x = 0; x < length; x++) {
			for (int32_t z = 0; z < width; z++) {
				if (output[convert2Dto1D(x, z, width)] == 0) {
					placeColumn(world, x + xOffset, z + zOffset, height, deadBlock);
				}
				else {
					placeColumn(world, x + xOffset, z + zOffset, height, liveBlock);
				}
			}
		}
	}

}