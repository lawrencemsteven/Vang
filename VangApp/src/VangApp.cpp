#include <Vang.h>

namespace Window = Vang::Windowing;

class PlayerMovementLayer : public Vang::Utility::Layers::Layer {
public:
	PlayerMovementLayer()
		: Layer{"Player Movement"} {}
	
	void onUpdate() override {
		if (Window::Input::isKeyPressed(Window::KEY::W)) {
			Vang::getPlayer().moveForward(Vang::Utility::Time::deltaTime());
		}
		else if (Window::Input::isKeyPressed(Window::KEY::S)) {
			Vang::getPlayer().moveForward(-Vang::Utility::Time::deltaTime());
		}

		if (Window::Input::isKeyPressed(Window::KEY::D)) {
			Vang::getPlayer().moveRight(Vang::Utility::Time::deltaTime());
		}
		else if (Window::Input::isKeyPressed(Window::KEY::A)) {
			Vang::getPlayer().moveRight(-Vang::Utility::Time::deltaTime());
		}

		if (Window::Input::isKeyPressed(Window::KEY::SPACE)) {
			Vang::getPlayer().moveUp(Vang::Utility::Time::deltaTime());
		}
		else if (Window::Input::isKeyPressed(Window::KEY::LEFT_SHIFT)) {
			Vang::getPlayer().moveUp(-Vang::Utility::Time::deltaTime());
		}
	}

	void onEvent(Window::Event& e) override {
		Window::EventDispatcher dispatcher{e};
		dispatcher.dispatch<Window::MouseMovedEvent>(
			std::bind(&PlayerMovementLayer::mouseMovedHandler, this, std::placeholders::_1));
	}

	bool mouseMovedHandler(Window::MouseMovedEvent& e) {
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