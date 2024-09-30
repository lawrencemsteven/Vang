#include <Vang.h>
#include "glad/glad.h"

class PlayerMovementLayer : public Vang::Utility::Layers::Layer {
public:
	PlayerMovementLayer()
		: Layer{"Player Movement"} {
		m_headlightID = Vang::getLightManager().createLight(glm::vec3(0.0, 0.0, 0.0),
															glm::vec3(1.0, 1.0, 1.0), 50, 1);
	}

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

		if (inputCache.isKeyPressed(Vang::Input::KEY::NUM_1)) {
			m_blockToBuild = Vang::Voxel::Blocks::Rainbow;
		}
		else if (inputCache.isKeyPressed(Vang::Input::KEY::NUM_2)) {
			m_blockToBuild = Vang::Voxel::Blocks::Glass;
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::R)) {
			Vang::Utility::Structure::generateStructure(
				28, 28, 456, 456, 6, Vang::Voxel::Blocks::Gray, Vang::Voxel::Blocks::Air);
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::F)) {
			if (!m_fKeyPressed) {
				m_fKeyPressed = true;
				if (Vang::getLightManager().getLight(m_headlightID).getRadius() == 0.0f) {
					Vang::getLightManager().getLight(m_headlightID).setRadius(50.0);
				}
				else {
					Vang::getLightManager().getLight(m_headlightID).setRadius(0.0);
				}
			}
		}
		else {
			m_fKeyPressed = false;
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::G)) {
			if (!m_gKeyPressed) {
				m_gKeyPressed	  = true;
				m_headlightFollow = !m_headlightFollow;
			}
		}
		else {
			m_gKeyPressed = false;
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
				const auto& raycast = Vang::getPlayer().getRaycastResult();

				if (raycast.hit) {
					const auto newBlockPosition = raycast.blockHitPosition - raycast.newBlockVector;
					const auto newBlock			= world.getBlock(newBlockPosition);
					if (newBlock != Vang::Voxel::Blocks::None) {
						world.setBlock(newBlockPosition, m_blockToBuild);
					}
				}
			}
		}
		else {
			m_rightClickPressed = false;
		}

		if (inputCache.isMouseButtonPressed(Vang::Input::MOUSE::BUTTON_LEFT)) {
			if (!m_leftClickPressed) {
				m_leftClickPressed	= true;
				auto& world			= Vang::getCurrentWorld();
				const auto& raycast = Vang::getPlayer().getRaycastResult();

				if (raycast.hit && raycast.blockHit != Vang::Voxel::Blocks::None) {
					world.setBlock(raycast.blockHitPosition, Vang::Voxel::Blocks::Air);
				}
			}
		}
		else {
			m_leftClickPressed = false;
		}

		if (m_headlightFollow) {
			Vang::getLightManager()
				.getLight(m_headlightID)
				.setPosition(Vang::getPlayer().getCamera().getPosition());
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
	bool m_fKeyPressed{false};
	bool m_gKeyPressed{false};
	bool m_headlightFollow{true};
	Vang::Utility::LightManager::LightID m_headlightID;

	Vang::Voxel::Blocks m_blockToBuild{Vang::Voxel::Blocks::Rainbow};
};




int main() {
	Vang::initialize();

	Vang::getLayerStack().pushLayer(new PlayerMovementLayer());

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

	// auto& m_uiManager = Vang::getUIManager();
	// auto menuID		  = m_uiManager.createMenu();
	// auto& menu		  = m_uiManager.getMenu(menuID);

	// menu.addPanel({-0.04f, 0.04f}, {0.04f, -0.04f}, 0.0f, {0.5f, 0.9f, 0.5f, 0.5f});
	// menu.addPanel({0.06f, -0.02f}, {-0.02f, 0.06f}, -0.2f, {0.5f, 0.5f, 0.9f, 0.25f});
	// menu.addPanel({-0.06f, 0.02f}, {0.02f, -0.06f}, 0.2f, {0.9f, 0.5f, 0.5f, 1.0f});
	// menu.addPanel({0.08f, 0.00f}, {0.00f, 0.08f}, -0.4f, {0.9f, 0.9f, 0.9f, 0.25f});

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

		// std::cout << "FPS: " << (1.0f / Vang::Utility::Time::deltaTime()) << std::endl;
	}
}