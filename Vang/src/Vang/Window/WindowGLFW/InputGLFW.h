#pragma once

#include "glad/glad.h"
#include "Vang/Utility/Input/Input.h"

namespace Vang {

	class GLFWInput : public Input {
	protected:
		bool isKeyPressedImpl(KEY keycode) override;
		bool isMouseButtonPressedImpl(MOUSE button) override;
		std::pair<float, float> getMousePositionImpl() override;
		float getMouseXImpl() override;
		float getMouseYImpl() override;
	};

}