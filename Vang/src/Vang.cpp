#include "Vang.h"

#ifdef VANG_WINDOW_GLFW
#	include "Vang/Window/WindowGLFW/WindowGLFW.h"
#	define VANG_CURRENT_WINDOW Vang::WindowGLFW
#endif

#ifdef VANG_GRAPHICSAPI_VULKAN
#	include "Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::GraphicsVulkan
#endif

VangInst& VangInst::Get(std::string_view applicationName) {
	static VangInst s_vangInst{applicationName};
	return s_vangInst;
}

std::string_view VangInst::getApplicationName() { return m_applicationName; }

void VangInst::beginFrame() {
	m_window->beginFrame();
}

void VangInst::endFrame() {
	if (m_toClose) cleanup();
}

void VangInst::toClose() {
	VANG_DEBUG("Vang Marked To Close");
	m_toClose = true;
}
bool VangInst::getToClose() { return m_toClose; }

void VangInst::cleanup() {
	m_window->close();
}

VangInst::VangInst(std::string_view applicationName)
	: m_applicationName{applicationName},
	  m_window{std::make_shared<VANG_CURRENT_WINDOW>(m_applicationName)},
	  m_graphicsAPI{std::make_shared<VANG_CURRENT_GRAPHICSAPI>()} {}