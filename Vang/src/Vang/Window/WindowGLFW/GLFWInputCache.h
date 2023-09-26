#pragma once

#include "glad/glad.h"
#include "Vang/Utility/Input/Input.h"

namespace Vang::Input {

	class GLFWInputCache : public InputCache {
	protected:
		bool isKeyPressed(KEY keycode) const override;
		bool isMouseButtonPressed(MOUSE button) const override;
		std::pair<float, float> getMousePosition() const override;
		float getMouseX() const override;
		float getMouseY() const override;
	};

}