#include "Vang.h"

using namespace Vang;

#define BIND_EVENT_FN(x) std::bind(&VangInst::x, this, std::placeholders::_1)

VangInst& VangInst::Get(const std::string& applicationName) {
	static VangInst s_vangInst{applicationName};
	return s_vangInst;
}

const std::string& VangInst::getApplicationName() {
	return m_applicationName;
}

Vang::Windowing::Window& VangInst::getWindow() {
	return *m_window;
}
const Vang::Windowing::Window& VangInst::getWindow() const {
	return *m_window;
}

gfx::GraphicsAPI& VangInst::getGraphicsAPI() {
	return *m_graphicsAPI;
}
const gfx::GraphicsAPI& VangInst::getGraphicsAPI() const {
	return *m_graphicsAPI;
}

Vang::Objects::Player& VangInst::getPlayer() {
	return m_player;
}

const Vang::Objects::Player& VangInst::getPlayer() const {
	return m_player;
}

Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint>& VangInst::getBlockManager() {
	return m_blockManager;
}

const Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint>& VangInst::getBlockManager() const {
	return m_blockManager;
}

Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint>& VangInst::getItemManager() {
	return m_itemManager;
}

const Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint>& VangInst::getItemManager() const {
	return m_itemManager;
}

Vang::Modding::ModManager& VangInst::getModManager() {
	return m_modManager;
}

const Vang::Modding::ModManager& VangInst::getModManager() const {
	return m_modManager;
}

void VangInst::initialize() {
	m_window = std::make_unique<VANG_CURRENT_WINDOW>(m_applicationName, 1920, 1080);
	m_window->setEventCallback(BIND_EVENT_FN(onEvent));
	m_graphicsAPI = std::make_unique<VANG_CURRENT_GRAPHICSAPI>(m_applicationName);
}

void VangInst::pushLayer(Vang::Utility::Layers::Layer* layer) {
	m_layerStack.pushLayer(layer);
}

void VangInst::pushOverlay(Vang::Utility::Layers::Layer* overlay) {
	m_layerStack.pushOverlay(overlay);
}

void VangInst::update() {
	m_window->update();
	m_graphicsAPI->update();

	for (Vang::Utility::Layers::Layer* layer : m_layerStack) {
		layer->onUpdate();
	}
	
	Vang::Utility::Time::updateDeltaTime();
	if (m_toClose) {
		cleanup();
	}
}

void VangInst::toClose() {
	VANG_DEBUG("Vang Marked To Close");
	m_toClose = true;
}
bool VangInst::getToClose() {
	return m_toClose;
}

void VangInst::onEvent(Vang::Windowing::Event& e) {
	for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
		(*--it)->onEvent(e);
		if (e.handled)
			break;
	}
}

void VangInst::cleanup() {
	m_window->close();
}

VangInst::VangInst(std::string_view applicationName)
	: m_applicationName{applicationName},
	  m_toClose{false} {
}