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

		if (inputCache.isMouseButtonPressed(Vang::Input::MOUSE::BUTTON_RIGHT)) {
			if (!m_rightClickPressed) {
				m_rightClickPressed = true;
				auto& world			= Vang::getCurrentWorld();
				auto& camera		= Vang::getPlayer().getCamera();

				const auto& raycast =
					Vang::VMath::raycast(world, camera.getPosition(), camera.getForward(), 5.0f);

				if (raycast.hit) {
					const auto newBlockPosition = raycast.blockHitPosition - raycast.newBlockVector;
					const auto newBlock			= world.getBlock(newBlockPosition);
					if (newBlock != Vang::Voxel::Blocks::None) {
						world.setBlock(newBlockPosition, Vang::Voxel::Blocks::Rainbow);
					}
				}
			}
		}
		else {
			m_rightClickPressed = false;
		}

		if (inputCache.isMouseButtonPressed(Vang::Input::MOUSE::BUTTON_LEFT)) {
			if (!m_leftClickPressed) {
				m_leftClickPressed = true;
				auto& world		   = Vang::getCurrentWorld();
				auto& camera	   = Vang::getPlayer().getCamera();

				const auto& raycast =
					Vang::VMath::raycast(world, camera.getPosition(), camera.getForward(), 5.0f);

				if (raycast.hit && raycast.blockHit != Vang::Voxel::Blocks::None) {
					world.setBlock(raycast.blockHitPosition, Vang::Voxel::Blocks::Air);
				}
			}
		}
		else {
			m_leftClickPressed = false;
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

private:
	bool m_rightClickPressed{false};
	bool m_leftClickPressed{false};
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