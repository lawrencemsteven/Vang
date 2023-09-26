#include "Vang.h"

namespace Vang {

	static bool s_running{true};
	static std::string s_applicationName{};
	static VANG_CURRENT_WINDOW s_window{s_applicationName, DEFAULT_WIDTH, DEFAULT_HEIGHT};
	static VANG_CURRENT_GRAPHICSAPI s_graphicsAPI{s_applicationName};
	static Vang::Objects::Player s_player{};
	static Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint> s_blockManager{};
	static Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint> s_itemManager{};
	static Vang::Modding::ModManager s_modManager{};
	static Vang::Utility::Layers::LayerStack s_layerStack{};
	static Vang::Windowing::EventHandler s_eventHandler{};

	bool getRunning() {
		return s_running;
	}

	void update() {
		s_window.update();
		s_graphicsAPI.update();
		s_layerStack.update();

		Vang::Utility::Time::updateDeltaTime();
	}

	void close() {
		s_window.close();
		s_running = false;
	}

	const std::string& getApplicationName() {
		return s_applicationName;
	}
	Vang::Windowing::Window& getWindow() {
		return s_window;
	}
	Vang::gfx::GraphicsAPI& getGraphicsAPI() {
		return s_graphicsAPI;
	}
	Vang::Objects::Player& getPlayer() {
		return s_player;
	}
	Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint>& getBlockManager() {
		return s_blockManager;
	}
	Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint>& getItemManager() {
		return s_itemManager;
	}
	Vang::Modding::ModManager& getModManager() {
		return s_modManager;
	}
	Vang::Utility::Layers::LayerStack& getLayerStack() {
		return s_layerStack;
	}
	Vang::Windowing::EventHandler& getEventHandler() {
		return s_eventHandler;
	}
}