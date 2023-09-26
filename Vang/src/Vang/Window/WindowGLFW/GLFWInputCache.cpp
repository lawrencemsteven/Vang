#include "GLFWInputCache.h"

#include "Vang.h"

namespace Vang::Input {

	bool GLFWInputCache::isKeyPressed(KEY keycode) const {
		auto window = static_cast<GLFWwindow*>(Vang::getWindow().getNativeWindow());
		auto state	= glfwGetKey(window, static_cast<int>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GLFWInputCache::isMouseButtonPressed(MOUSE button) const {
		auto window = static_cast<GLFWwindow*>(Vang::getWindow().getNativeWindow());
		auto state	= glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GLFWInputCache::getMousePosition() const {
		auto window = static_cast<GLFWwindow*>(Vang::getWindow().getNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return {static_cast<float>(xPos), static_cast<float>(yPos)};
	}

	float GLFWInputCache::getMouseX() const {
		const auto [x, y] = getMousePosition();
		return x;
	}

	float GLFWInputCache::getMouseY() const {
		const auto [x, y] = getMousePosition();
		return y;
	}

}