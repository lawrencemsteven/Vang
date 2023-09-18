#include <Vang.h>

namespace Window = Vang::Windowing;

class PlayerMovementLayer : public Vang::Utility::Layers::Layer {
public:
	PlayerMovementLayer()
		: Layer{"Player Movement"} {}
	
	void onUpdate() override {
		if (Window::Input::isKeyPressed(Window::KEY::W)) {
			VangInst::Get().getPlayer().moveForward(Vang::Utility::Time::deltaTime());
		}
		else if (Window::Input::isKeyPressed(Window::KEY::S)) {
			VangInst::Get().getPlayer().moveForward(-Vang::Utility::Time::deltaTime());
		}

		if (Window::Input::isKeyPressed(Window::KEY::D)) {
			VangInst::Get().getPlayer().moveRight(Vang::Utility::Time::deltaTime());
		}
		else if (Window::Input::isKeyPressed(Window::KEY::A)) {
			VangInst::Get().getPlayer().moveRight(-Vang::Utility::Time::deltaTime());
		}

		if (Window::Input::isKeyPressed(Window::KEY::SPACE)) {
			VangInst::Get().getPlayer().moveUp(Vang::Utility::Time::deltaTime());
		}
		else if (Window::Input::isKeyPressed(Window::KEY::LEFT_SHIFT)) {
			VangInst::Get().getPlayer().moveUp(-Vang::Utility::Time::deltaTime());
		}
	}

	void onEvent(Window::Event& e) override {
		Window::EventDispatcher dispatcher{e};
		dispatcher.dispatch<Window::MouseMovedEvent>(
			std::bind(&PlayerMovementLayer::mouseMovedHandler, this, std::placeholders::_1));
	}

	bool mouseMovedHandler(Window::MouseMovedEvent& e) {
		VangInst::Get().getPlayer().getCamera().mouseRotate(e.getX(), -e.getY());
		return true;
	}
};

int main() {
	VangInst& vangInst = VangInst::Get("VangApp");
	vangInst.initialize();
	vangInst.pushLayer(new PlayerMovementLayer());
	bool running	   = true;
	while (running) {
		vangInst.update();

		if (vangInst.getToClose())
			running = false;
	}
}