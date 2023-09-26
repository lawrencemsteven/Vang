#include <Vang.h>

class PlayerMovementLayer : public Vang::Utility::Layers::Layer {
public:
	PlayerMovementLayer()
		: Layer{"Player Movement"} {}
	
	void onUpdate() override {
		const auto& inputCache = Vang::getInputCache();

		if (inputCache.isKeyPressed(Vang::Input::KEY::W)) {
			Vang::getPlayer().moveForward(Vang::Utility::Time::deltaTime());
		}
		else if (inputCache.isKeyPressed(Vang::Input::KEY::S)) {
			Vang::getPlayer().moveForward(-Vang::Utility::Time::deltaTime());
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::D)) {
			Vang::getPlayer().moveRight(Vang::Utility::Time::deltaTime());
		}
		else if (inputCache.isKeyPressed(Vang::Input::KEY::A)) {
			Vang::getPlayer().moveRight(-Vang::Utility::Time::deltaTime());
		}

		if (inputCache.isKeyPressed(Vang::Input::KEY::SPACE)) {
			Vang::getPlayer().moveUp(Vang::Utility::Time::deltaTime());
		}
		else if (inputCache.isKeyPressed(Vang::Input::KEY::LEFT_SHIFT)) {
			Vang::getPlayer().moveUp(-Vang::Utility::Time::deltaTime());
		}
	}

	void onEvent(Vang::Utility::Events::Event& e) override {
		Vang::Utility::Events::EventDispatcher dispatcher{e};
		dispatcher.dispatch<Vang::Utility::Events::MouseMovedEvent>(
			std::bind(&PlayerMovementLayer::mouseMovedHandler, this, std::placeholders::_1));
	}

	bool mouseMovedHandler(Vang::Utility::Events::MouseMovedEvent& e) {
		Vang::getPlayer().getCamera().mouseRotate(e.getX(), -e.getY());
		return true;
	}
};

int main() {
	Vang::getLayerStack().pushLayer(new PlayerMovementLayer());

	while (Vang::getRunning()) {
		Vang::update();
	}
}