#pragma once

#ifdef VANG_GRAPHICSAPI_VULKAN

#elif VANG_GRAPHICSAPI_OPENGL
#	include "Vang/GraphicsAPI/GraphicsOpenGL/Buffers/UI/ColoredPanelBuffer.h"
#endif

namespace Vang::gfx::Components {

	std::unique_ptr<Vang::gfx::Generic::Buffers::UI::ColoredPanelBuffer> getColoredPanelBuffer() {
		return std::make_unique<Vang::gfx::OpenGL::Buffers::UI::ColoredPanelBuffer>();
	}

}