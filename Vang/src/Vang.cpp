#include "Vang.h"

#ifdef VANG_GRAPHICSAPI_VULKAN
#	include "Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::Vulkan::GraphicsVulkan
#elif VANG_GRAPHICSAPI_OPENGL
#	include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::OpenGL::GraphicsOpenGL
#endif

#ifdef VANG_WINDOW_GLFW
#	include "Vang/Window/WindowGLFW/WindowGLFW.h"
#	define VANG_CURRENT_WINDOW Vang::WindowGLFW
#endif

VangInst& VangInst::Get(std::string_view applicationName) {
	static VangInst s_vangInst{applicationName};
	return s_vangInst;
}

std::string_view VangInst::getApplicationName() { return m_applicationName; }

Vang::Window& VangInst::getWindow() { return *m_window; }
const Vang::Window& VangInst::getWindow() const { return *m_window; }

Vang::gfx::GraphicsAPI& VangInst::getGraphicsAPI() { return *m_graphicsAPI; }
const Vang::gfx::GraphicsAPI& VangInst::getGraphicsAPI() const {
	return *m_graphicsAPI;
}

Vang::Player& VangInst::getPlayer() {
	return *m_player;
}

const Vang::Player& VangInst::getPlayer() const {
	return *m_player;
}

void VangInst::beginFrame() {
	m_window->beginFrame();
	m_graphicsAPI->beginFrame();
}

void VangInst::endFrame() {

	if (m_toClose) cleanup();
}

void VangInst::toClose() {
	VANG_DEBUG("Vang Marked To Close");
	m_toClose = true;
}
bool VangInst::getToClose() { return m_toClose; }

void VangInst::cleanup() { m_window->close(); }

VangInst::VangInst(std::string_view applicationName)
	: m_applicationName{applicationName},
	  m_toClose{false},
	  m_window{std::make_unique<VANG_CURRENT_WINDOW>(*this, m_applicationName)},
	  m_graphicsAPI{std::make_unique<VANG_CURRENT_GRAPHICSAPI>(*this, m_applicationName)},
	  m_player{std::make_unique<Vang::Player>(*this)} {
}