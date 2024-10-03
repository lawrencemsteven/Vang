#include "PlayerMovement.h"
#include "UISetup.h"

int main() {
	Vang::initialize();

	Vang::getLayerStack().pushLayer(new PlayerMovementLayer());

	Vang::getUIManager().pushMenu(std::make_shared<SampleMenu>());

	auto& world = Vang::getCurrentWorld();

	// Set bottom level of blocks
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t z = 0; z < 576; z++) {
			world.setBlock({x, 0, z}, Vang::Voxel::Blocks::White);
		}
	}

	// Set top level of blocks
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t z = 0; z < 576; z++) {
			world.setBlock({x, 575, z}, Vang::Voxel::Blocks::Blue);
		}
	}

	// Demo block tower
	for (uint32_t i = 2; i < 16; i++) {
		world.setBlock({10, i - 1, 20}, static_cast<Vang::Voxel::Blocks>(i));
	}

	Vang::Utility::Structure::generateStructure(28, 28, 456, 456, 6, Vang::Voxel::Blocks::Gray,
												Vang::Voxel::Blocks::Air);

	auto& lightManager = Vang::getLightManager();
	auto light1ID =
		lightManager.createLight(glm::vec3(5.0, 5.0, 5.0), glm::vec3(1.0, 1.0, 1.0), 50, 1);
	auto light2ID =
		lightManager.createLight(glm::vec3(15.0, 5.0, 5.0), glm::vec3(0.0, 2.0, 2.0), 50, 1);

	const float lightRadius = 5.0f;
	const float spinTime	= 10.0f;

	Vang::getPlayer().setPosition(glm::vec3(50.0, 15.0, 50.0));

	while (Vang::getRunning()) {
		Vang::update();

		lightManager.getLight(light1ID).setPosition(glm::vec3(
			50.0,
			15.0 + lightRadius *
					   cos(std::fmod(Vang::Utility::Time::timeSinceStart(), spinTime * 2.0 * M_PI)),
			50.0));
		lightManager.getLight(light2ID).setPosition(glm::vec3(
			50.0 + lightRadius *
					   cos(std::fmod(Vang::Utility::Time::timeSinceStart(), spinTime * 2.0 * M_PI)),
			15.0,
			50.0 + lightRadius * sin(std::fmod(Vang::Utility::Time::timeSinceStart(),
											   spinTime * 2.0 * M_PI))));
	}
}