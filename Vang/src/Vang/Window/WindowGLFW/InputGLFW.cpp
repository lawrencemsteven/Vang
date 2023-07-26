#include "InputGLFW.h"

#include "Vang.h"

namespace Vang {

	Input* Input::s_instance = new GLFWInput();

	bool GLFWInput::isKeyPressedImpl(KEY keycode) {
		auto window = static_cast<GLFWwindow*>(VangInst::Get().getWindow().getNativeWindow());
		auto state	= glfwGetKey(window, static_cast<int>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GLFWInput::isMouseButtonPressedImpl(MOUSE button) {
		auto window = static_cast<GLFWwindow*>(VangInst::Get().getWindow().getNativeWindow());
		auto state	= glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GLFWInput::getMousePositionImpl() {
		auto window = static_cast<GLFWwindow*>(VangInst::Get().getWindow().getNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return {static_cast<float>(xPos), static_cast<float>(yPos)};
	}

	float GLFWInput::getMouseXImpl() {
		auto [x, y] = getMousePositionImpl();
		return x;
	}

	float GLFWInput::getMouseYImpl() {
		auto [x, y] = getMousePositionImpl();
		return y;
	}

}