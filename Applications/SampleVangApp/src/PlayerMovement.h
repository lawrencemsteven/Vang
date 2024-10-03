#include <Vang.h>

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

		if (m_headlightFollow) {
			Vang::getLightManager()
				.getLight(m_headlightID)
				.setPosition(Vang::getPlayer().getCamera().getPosition());
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::ESCAPE)) {
			if (!m_escapeKeyPressed) {
				m_escapeKeyPressed = true;
				Vang::getWindow().setMouseEnabled(!Vang::getWindow().getMouseEnabled());
			}
		}
		else {
			m_escapeKeyPressed = false;
		}

		if (Vang::getWindow().getMouseEnabled()) {
			return;
		}

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
	}

	void onEvent(Vang::Utility::Events::Event& e) override {
		Vang::Utility::Events::EventDispatcher dispatcher{e};
		dispatcher.dispatch<Vang::Utility::Events::MouseMovedEvent>(
			std::bind(&PlayerMovementLayer::mouseMovedHandler, this, std::placeholders::_1));
	}

	bool mouseMovedHandler(Vang::Utility::Events::MouseMovedEvent& e) {
		if (Vang::getWindow().getMouseEnabled()) {
			return false;
		}

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
	bool m_escapeKeyPressed{false};
	Vang::Utility::LightManager::LightID m_headlightID;

	Vang::Voxel::Blocks m_blockToBuild{Vang::Voxel::Blocks::Rainbow};
};