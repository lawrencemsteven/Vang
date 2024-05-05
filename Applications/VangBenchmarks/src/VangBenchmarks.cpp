#include <Vang.h>

int main() {
	auto& world = Vang::getCurrentWorld();

	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t y = 0; y < 576; y++) {
			for (uint32_t z = 0; z < 576; z++) {
				world.setBlock(x, y, z, Vang::Voxel::Blocks::Gray);
			}
		}
	}

	for (uint32_t x = 0; x < 576; x++) {
		world.setBlock(x, 288, 288, Vang::Voxel::Blocks::Air);
	}

	Vang::getPlayer().setPosition({0.5f, 288.0f, 288.0f});

	while (Vang::getRunning()) {
		Vang::update();

		Vang::Utility::FileIO::FileWriter file(std::filesystem::path{"./VangBenchmarks.txt"});

		file.write("1");
		file.write("2");
		file.writeLine("3");
		file.writeLine("Hello World!");
	}
}