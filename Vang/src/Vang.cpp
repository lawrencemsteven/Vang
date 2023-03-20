#include "Vang.h"

#ifdef VANG_WINDOW_GLFW
#include "Vang/Window/WindowGLFW/WindowGLFW.h"
#define VANG_CURRENT_WINDOW Vang::WindowGLFW
#endif

#ifdef VANG_GRAPHICSAPI_VULKAN
#include "Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
#define VANG_CURRENT_GRAPHICSAPI Vang::GraphicsVulkan
#endif

VangInst& VangInst::Get(std::string_view applicationName) {
	static VangInst s_vangInst{applicationName};
	return s_vangInst;
}

void VangInst::beginFrame() {}

void VangInst::endFrame() {}

void VangInst::cleanup() {}

VangInst::VangInst(std::string_view applicationName)
	: m_applicationName{applicationName},
	  m_window{std::make_shared<VANG_CURRENT_WINDOW>()},
	  m_graphicsAPI{std::make_shared<VANG_CURRENT_GRAPHICSAPI>()} {}