#pragma once

#include "Vang/Utility/Camera/Camera.h"

namespace Vang::gfx {

	class GraphicsAPI {
	public:
		GraphicsAPI();
		GraphicsAPI(std::string_view application_name);

		virtual void update() = 0;

		std::string_view getApplicationName();

		virtual void windowResize(uint32_t width, uint32_t height) = 0;

		virtual void displayCamera(const Vang::Objects::Camera& camera) = 0;

	protected:
		std::string_view m_applicationName;
	};

}
