#include <iostream>
#include <cstring>
#include <vector>

int convert2Dto1D(int x, int y, int width) {
	return x + y * width;
}

void printDungeon(std::vector<int>& dungeon, int height, int width) {
	int i = 0;
	int j = 0;
	while (i < width) {
		while (j < height) {
			if (dungeon[convert2Dto1D(i, j, width)] == 1) {
				printf("#");
			}
			else {
				printf("`");
			}
			// printf("%d", dungeon[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
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
				living += 1;
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

void iterator(std::vector<int>& dungeon, int height, int width, int birthT, int surviveT,
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
	iterator(output, height, width, birthT, surviveT, iterations);
	return output;
}

int main() {

	int height = 180;
	int width  = 180;
	// lifeRate is percent chance representation
	int lifeRate   = 45;
	int iterations = 8;
	int birthT	   = 5;
	int surviveT   = 4;
	// int output[40][40];
	std::vector<int> output{makeDungeon(height, width, lifeRate, iterations, birthT, surviveT)};
	printDungeon(output, height, width);
	return 0;
}