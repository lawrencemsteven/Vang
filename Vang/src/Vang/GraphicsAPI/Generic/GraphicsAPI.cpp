#include "GraphicsAPI.h"

namespace Vang::gfx {

	GraphicsAPI::GraphicsAPI()
		: m_applicationName{""} {
	}

	GraphicsAPI::GraphicsAPI(std::string_view applicationName)
		: m_applicationName{applicationName} {
	}

	std::string_view GraphicsAPI::getApplicationName() {
		return m_applicationName;
	}

}
