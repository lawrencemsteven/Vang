#include "GraphicsAPI.h"

namespace Vang::gfx {

	void GraphicsAPI::initialize() {
		m_applicationName = "";
	}

	void GraphicsAPI::initialize(std::string_view applicationName) {
		m_applicationName = applicationName;
	}

	std::string_view GraphicsAPI::getApplicationName() {
		return m_applicationName;
	}
}
