#include <Vang.h>

class PlayerMovementLayer : public Vang::Layer {
public:
	PlayerMovementLayer()
		: Layer{"Player Movement"} {}
	
	void onUpdate() override {
		if (Vang::Input::isKeyPressed(Vang::KEY::W)) {
			VangInst::Get().getPlayer().moveForward(Vang::Time::deltaTime());
		}
		else if (Vang::Input::isKeyPressed(Vang::KEY::S)) {
			VangInst::Get().getPlayer().moveForward(-Vang::Time::deltaTime());
		}

		if (Vang::Input::isKeyPressed(Vang::KEY::D)) {
			VangInst::Get().getPlayer().moveRight(Vang::Time::deltaTime());
		}
		else if (Vang::Input::isKeyPressed(Vang::KEY::A)) {
			VangInst::Get().getPlayer().moveRight(-Vang::Time::deltaTime());
		}

		if (Vang::Input::isKeyPressed(Vang::KEY::SPACE)) {
			VangInst::Get().getPlayer().moveUp(Vang::Time::deltaTime());
		}
		else if (Vang::Input::isKeyPressed(Vang::KEY::LEFT_SHIFT)) {
			VangInst::Get().getPlayer().moveUp(-Vang::Time::deltaTime());
		}
	}

	void onEvent(Vang::Event& e) override {
		Vang::EventDispatcher dispatcher{e};
		dispatcher.dispatch<Vang::MouseMovedEvent>(
			std::bind(&PlayerMovementLayer::mouseMovedHandler, this, std::placeholders::_1));
	}

	bool mouseMovedHandler(Vang::MouseMovedEvent& e) {
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