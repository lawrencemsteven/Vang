#include "Vang.h"

namespace Vang {

	static bool s_running{true};
	static std::string s_applicationName{};
	static VANG_CURRENT_WINDOW s_window{};
	static VANG_CURRENT_GRAPHICSAPI s_graphicsAPI{};
	static Vang::Voxel::World s_currentWorld{};
	static Vang::Objects::Player s_player{};
	static Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint> s_blockManager{};
	static Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint> s_itemManager{};
	static Vang::Modding::ModManager s_modManager{};
	static Vang::Utility::Layers::LayerStack s_layerStack{};
	static Vang::Utility::Events::EventHandler s_eventHandler{};
	static VANG_CURRENT_WINDOW_INPUT s_inputCache{};
	static Vang::Utility::EntityManager s_entityManager{};

	void cleanup() {
		s_window.close();
	}

	void initialize() {
		s_running;
		s_window.initialize(s_applicationName, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_FULLSCREEN);
		s_graphicsAPI.initialize(s_applicationName);
		s_player.initialize();
	}

	bool getRunning() {
		return s_running;
	}

	void update() {
		Vang::Utility::Time::updateDeltaTime();

		s_window.update();
		s_layerStack.update();
		s_graphicsAPI.update();

		if (!s_running) {
			cleanup();
		}

		// TODO: Figure something out for this to not kill framerate
		// std::this_thread::sleep_for(std::chrono::microseconds(100));
	}

	void close() {
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
	Vang::Utility::Events::EventHandler& getEventHandler() {
		return s_eventHandler;
	}
	Vang::Input::InputCache& getInputCache() {
		return s_inputCache;
	}
	Vang::Voxel::World& getCurrentWorld() {
		return s_currentWorld;
	}
	Vang::Utility::EntityManager& getEntityManager() {
		return s_entityManager;
	}
}
