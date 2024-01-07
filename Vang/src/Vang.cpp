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
	static Vang::Utility::Events::EventHandler s_eventHandler{};
	static VANG_CURRENT_WINDOW_INPUT s_inputCache{};

	static std::unordered_map<uint32_t, std::reference_wrapper<Vang::Voxel::ChunkLoader>>
		s_chunkLoaders;
	static uint32_t s_chunkLoaderCount{0};

	void cleanup() {
		s_window.close();
	}

	bool getRunning() {
		return s_running;
	}

	void update() {
		Vang::Utility::Time::updateDeltaTime();

		s_window.update();
		s_layerStack.update();
		s_graphicsAPI.update();

		for (const auto& [chunkLoaderId, chunkLoader] : s_chunkLoaders) {
			chunkLoader.get().update();
		}

		if (!s_running) {
			cleanup();
		}
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
}


namespace Vang::detail {

	uint32_t addChunkLoader(Vang::Voxel::ChunkLoader& chunkLoader) {
		s_chunkLoaders.emplace(s_chunkLoaderCount, chunkLoader);
		return ++s_chunkLoaderCount;
	}

	void removeChunkLoader(uint32_t chunkLoaderId) {
		const auto it = s_chunkLoaders.find(chunkLoaderId);
		s_chunkLoaders.erase(it);
	}

}
