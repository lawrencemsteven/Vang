#include "Input.h"

namespace Vang::Windowing {

	bool Input::isKeyPressed(KEY keycode) {
		return s_instance->isKeyPressedImpl(keycode);
	}

	bool Input::isMouseButtonPressed(MOUSE button) {
		return s_instance->isMouseButtonPressedImpl(button);
	}

	std::pair<float, float> Input::getMousePosition() {
		return s_instance->getMousePositionImpl();
	}

	float Input::getMouseX() {
		return s_instance->getMouseXImpl();
	}

	float Input::getMouseY() {
		return s_instance->getMouseYImpl();
	}

}