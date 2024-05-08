#include <Vang.h>

bool sceneFrameSkip(const uint32_t amount) {
	static uint32_t skippedFrames{0};
	skippedFrames++;
	if (skippedFrames >= amount) {
		skippedFrames = 0;
		return true;
	}
	return false;
}

bool initializeScene() {
	static float sceneTime{1.0f};
	sceneTime -= Vang::Utility::Time::deltaTime();
	return sceneTime <= 0.0f;
}

bool loadTunnelScene() {
	auto& world = Vang::getCurrentWorld();

	// Fill World
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t y = 0; y < 576; y++) {
			for (uint32_t z = 0; z < 576; z++) {
				world.setBlock({x, y, z}, Vang::Voxel::Blocks::Gray);
			}
		}
	}

	// Clear Tunnel
	const uint32_t radius = 0;
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t yMod = 288 - radius; yMod <= 288 + radius; yMod++) {
			for (uint32_t zMod = 288 - radius; zMod <= 288 + radius; zMod++) {
				world.setBlock({x, yMod, zMod}, Vang::Voxel::Blocks::Air);
			}
		}
	}

	Vang::getPlayer().getCamera().rotateRight(90.0f);

	return true;
}

bool runTunnelScene() {
	const float totalSceneTime{10.0f};
	static float sceneTime{totalSceneTime};
	const glm::vec3 startPos{0.0f, 288.0f, 288.0f};
	const glm::vec3 endPos{575.0f, 288.0f, 288.0f};

	const glm::vec3 newPos = glm::mix(endPos, startPos, sceneTime / totalSceneTime);

	Vang::getPlayer().setPosition(newPos);

	sceneTime -= Vang::Utility::Time::deltaTime();

	return sceneTime <= 0.0f;
}

bool loadStaircaseScene() {
	auto& world = Vang::getCurrentWorld();

	// Fill World
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t y = 0; y < 576; y++) {
			for (uint32_t z = 0; z < 576; z++) {
				world.setBlock({x, y, z}, Vang::Voxel::Blocks::Gray);
			}
		}
	}

	// Clear Staircase
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t stepWidth = 0; stepWidth < 3; stepWidth++) {
			for (uint32_t stepHeight = 0; stepHeight < 4; stepHeight++) {
				const uint32_t stepX = std::clamp(x + stepWidth, 0U, 575U);
				const uint32_t stepY = std::clamp(x + stepHeight, 0U, 575U);
				world.setBlock({stepX, stepY, 288}, Vang::Voxel::Blocks::Air);
			}
		}
	}

	// Vang::getPlayer().getCamera().rotateRight(90.0f);
	Vang::getPlayer().getCamera().rotateUp(45.0f);

	return true;
}

bool runStaircaseScene() {
	const float totalSceneTime{10.0f};
	static float sceneTime{totalSceneTime};
	const glm::vec3 startPos{0.0f, 1.0f, 288.0f};
	const glm::vec3 endPos{574.0f, 575.0f, 288.0f};

	const glm::vec3 newPos = glm::mix(endPos, startPos, sceneTime / totalSceneTime);

	Vang::getPlayer().setPosition(newPos);

	sceneTime -= Vang::Utility::Time::deltaTime();

	return sceneTime <= 0.0f;
}

bool loadEmptyScene() {
	auto& world = Vang::getCurrentWorld();

	// Fill World
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t y = 0; y < 576; y++) {
			for (uint32_t z = 0; z < 576; z++) {
				world.setBlock({x, y, z}, Vang::Voxel::Blocks::Air);
			}
		}
	}

	// Fill Floor
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t z = 0; z < 576; z++) {
			world.setBlock({x, 0, z}, Vang::Voxel::Blocks::Gray);
		}
	}

	Vang::getPlayer().getCamera().rotateRight(45.0f);
	Vang::getPlayer().getCamera().rotateUp(-135.0f);

	return true;
}

bool runEmptyScene() {
	const float totalSceneTime{10.0f};
	static float sceneTime{totalSceneTime};
	const glm::vec3 startPos{0.0f, 575.0f, 0.0f};
	const glm::vec3 endPos{575.0f, 575.0f, 575.0f};

	const glm::vec3 newPos = glm::mix(endPos, startPos, sceneTime / totalSceneTime);

	Vang::getPlayer().setPosition(newPos);

	sceneTime -= Vang::Utility::Time::deltaTime();

	return sceneTime <= 0.0f;
}

int main() {
	uint32_t currentScene{0};
	uint32_t prevScene{0};

	const uint32_t framesToSkip{10};

	Vang::Utility::FileIO::FileWriter outFile{"./VangBenchmarks.csv"};
	outFile.write("0,");

	while (Vang::getRunning()) {
		switch (currentScene) {
			case 0: currentScene += static_cast<uint32_t>(initializeScene()); break;
			case 1: currentScene += static_cast<uint32_t>(sceneFrameSkip(framesToSkip)); break;
			case 2: currentScene += static_cast<uint32_t>(loadTunnelScene()); break;
			case 3: currentScene += static_cast<uint32_t>(sceneFrameSkip(framesToSkip)); break;
			case 4: currentScene += static_cast<uint32_t>(runTunnelScene()); break;
			case 5: currentScene += static_cast<uint32_t>(sceneFrameSkip(framesToSkip)); break;
			case 6: currentScene += static_cast<uint32_t>(loadStaircaseScene()); break;
			case 7: currentScene += static_cast<uint32_t>(sceneFrameSkip(framesToSkip)); break;
			case 8: currentScene += static_cast<uint32_t>(runStaircaseScene()); break;
			case 9: currentScene += static_cast<uint32_t>(sceneFrameSkip(framesToSkip)); break;
			case 10: currentScene += static_cast<uint32_t>(loadEmptyScene()); break;
			case 11: currentScene += static_cast<uint32_t>(sceneFrameSkip(framesToSkip)); break;
			case 12: currentScene += static_cast<uint32_t>(runEmptyScene()); break;
			case 13: Vang::close();
		}

		outFile.write(std::to_string(Vang::Utility::Time::deltaTime()) + ",");

		if (prevScene != currentScene) {
			std::cout << "Switching to Scene: " << currentScene << std::endl;
			prevScene = currentScene;
			outFile.writeLine("");
			outFile.write(std::to_string(currentScene) + ",");
		}

		Vang::update();
	}
}