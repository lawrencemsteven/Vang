#pragma once

#include "Vang/Utility/Camera/Camera.h"

namespace Vang::gfx {

	class GraphicsAPI {
	public:
		GraphicsAPI();
		GraphicsAPI(std::string_view application_name);

		virtual void beginFrame() = 0;
		virtual void endFrame()	  = 0;

		std::string_view getApplicationName();

		virtual void windowResize(uint32_t width, uint32_t height) = 0;

		virtual void displayCamera(const Camera& camera) = 0;

	protected:
		std::string_view m_applicationName;
	};

}
