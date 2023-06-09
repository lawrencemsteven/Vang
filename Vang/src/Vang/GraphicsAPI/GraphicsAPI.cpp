#include "GraphicsAPI.h"

namespace Vang::gfx {

	GraphicsAPI::GraphicsAPI(VangInst& vangInst)
		: m_vangInst{vangInst},
		  m_applicationName{""} {}

	GraphicsAPI::GraphicsAPI(VangInst& vangInst, std::string_view applicationName)
		: m_vangInst{vangInst},
		  m_applicationName{applicationName} {}

	std::string_view GraphicsAPI::getApplicationName() { return m_applicationName; }

}
