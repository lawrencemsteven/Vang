#include "Vang.h"

#define BIND_EVENT_FN(x) std::bind(&VangInst::x, this, std::placeholders::_1)

VangInst& VangInst::Get(const std::string& applicationName) {
	static VangInst s_vangInst{applicationName};
	return s_vangInst;
}

const std::string& VangInst::getApplicationName() {
	return m_applicationName;
}

Vang::Window& VangInst::getWindow() {
	return *m_window;
}
const Vang::Window& VangInst::getWindow() const {
	return *m_window;
}

Vang::gfx::GraphicsAPI& VangInst::getGraphicsAPI() {
	return *m_graphicsAPI;
}
const Vang::gfx::GraphicsAPI& VangInst::getGraphicsAPI() const {
	return *m_graphicsAPI;
}

Vang::Player& VangInst::getPlayer() {
	return *m_player;
}

const Vang::Player& VangInst::getPlayer() const {
	return *m_player;
}

void VangInst::initialize() {
	m_window	  = std::make_unique<VANG_CURRENT_WINDOW>(m_applicationName, 1920, 1080);
	m_window->setEventCallback(BIND_EVENT_FN(onEvent));
	m_graphicsAPI = std::make_unique<VANG_CURRENT_GRAPHICSAPI>(m_applicationName);
	m_player	  = std::make_unique<Vang::Player>();
}

void VangInst::beginFrame() {
	m_window->beginFrame();
	m_graphicsAPI->beginFrame();
}

void VangInst::endFrame() {

	if (m_toClose)
		cleanup();
}

void VangInst::toClose() {
	VANG_DEBUG("Vang Marked To Close");
	m_toClose = true;
}
bool VangInst::getToClose() {
	return m_toClose;
}

void VangInst::onEvent(Vang::Event& e) {
	Vang::EventDispatcher dispatcher{e};
	dispatcher.dispatch<Vang::MouseMovedEvent>(BIND_EVENT_FN(mouseMovedEventHandler));
}

bool VangInst::mouseMovedEventHandler(Vang::MouseMovedEvent& e) {
	m_player->getCamera().mouseRotate(e.getX(), -e.getY());
	return true;
}

void VangInst::cleanup() {
	m_window->close();
}

VangInst::VangInst(std::string_view applicationName)
	: m_applicationName{applicationName},
	  m_toClose{false} {
}