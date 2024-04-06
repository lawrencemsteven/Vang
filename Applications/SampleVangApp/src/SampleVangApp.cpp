#include <Vang.h>

class PlayerMovementLayer : public Vang::Utility::Layers::Layer {
public:
	PlayerMovementLayer()
		: Layer{"Player Movement"} {}

	void onUpdate() override {
		const auto& inputCache = Vang::getInputCache();
		auto& player		   = Vang::getPlayer();

		if (inputCache.isKeyPressed(Vang::Input::KEY::LEFT_CONTROL) ||
			inputCache.isMouseButtonPressed(Vang::Input::MOUSE::BUTTON_5)) {
			player.setSpeed(20.0f);
		}
		else {
			player.setSpeed(3.0f);
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::W)) {
			player.moveForward(Vang::Utility::Time::deltaTime());
		}
		else if (inputCache.isKeyPressed(Vang::Input::KEY::S)) {
			player.moveForward(-Vang::Utility::Time::deltaTime());
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::D)) {
			player.moveRight(Vang::Utility::Time::deltaTime());
		}
		else if (inputCache.isKeyPressed(Vang::Input::KEY::A)) {
			player.moveRight(-Vang::Utility::Time::deltaTime());
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::R)) {
			Vang::Utility::Structure::generateStructure(
				28, 28, 456, 456, 6, Vang::Voxel::Blocks::Gray, Vang::Voxel::Blocks::Air);
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::SPACE)) {
			player.moveUp(Vang::Utility::Time::deltaTime());
		}
		else if (inputCache.isKeyPressed(Vang::Input::KEY::LEFT_SHIFT)) {
			player.moveUp(-Vang::Utility::Time::deltaTime());
		}
	}

	void onEvent(Vang::Utility::Events::Event& e) override {
		Vang::Utility::Events::EventDispatcher dispatcher{e};
		dispatcher.dispatch<Vang::Utility::Events::MouseMovedEvent>(
			std::bind(&PlayerMovementLayer::mouseMovedHandler, this, std::placeholders::_1));
	}

	bool mouseMovedHandler(Vang::Utility::Events::MouseMovedEvent& e) {
		auto& playerCamera = Vang::getPlayer().getCamera();

		playerCamera.mouseRotate(e.getX(), -e.getY());
		return true;
	}
};




int main() {
	Vang::getLayerStack().pushLayer(new PlayerMovementLayer());

	auto& world = Vang::getCurrentWorld();

	// Set bottom level of blocks
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t z = 0; z < 576; z++) {
			world.setBlock({x, 0, z}, Vang::Voxel::Blocks::Green);
		}
	}

	// Set top level of blocks
	for (uint32_t x = 0; x < 576; x++) {
		for (uint32_t z = 0; z < 576; z++) {
			world.setBlock({x, 575, z}, Vang::Voxel::Blocks::Blue);
		}
	}

	// Demo block tower
	for (uint32_t i = 2; i < 15; i++) {
		world.setBlock({10, i - 1, 20}, static_cast<Vang::Voxel::Blocks>(i));
	}

	Vang::Utility::Structure::generateStructure(28, 28, 456, 456, 6, Vang::Voxel::Blocks::Gray,
												Vang::Voxel::Blocks::Air);

	while (Vang::getRunning()) {
		Vang::update();
		// std::cout << "FPS: " << (1.0f / Vang::Utility::Time::deltaTime()) << std::endl;
	}
}