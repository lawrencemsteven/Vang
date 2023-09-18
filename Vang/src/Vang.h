#pragma once

#ifdef VANG_GRAPHICSAPI_VULKAN
#	include "Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::Vulkan::GraphicsVulkan
#elif VANG_GRAPHICSAPI_OPENGL
#	include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::OpenGL::GraphicsOpenGL
#endif

#ifdef VANG_WINDOW_GLFW
#	include "Vang/Window/WindowGLFW/WindowGLFW.h"
#	define VANG_CURRENT_WINDOW Vang::Windowing::WindowGLFW
#endif

#include "Vang/GraphicsAPI/Generic/GraphicsAPI.h"
#include "Vang/Items/ItemBlueprint.h"
#include "Vang/Modding/ModManager.h"
#include "Vang/Utility/BlueprintContainer/BlueprintContainer.h"
#include "Vang/Utility/Events/Event.h"
#include "Vang/Utility/Events/MouseEvent.h"
#include "Vang/Utility/Layers/LayerStack.h"
#include "Vang/Utility/Player/Player.h"
#include "Vang/Utility/Time/Time.h"
#include "Vang/Voxel/BlockBlueprint.h"
#include "Vang/Voxel/Universe.h"
#include "Vang/Window/Window.h"

class VangInst {
public:
	static VangInst& Get(const std::string& applicationName = "");

	const std::string& getApplicationName();

	Vang::Windowing::Window& getWindow();
	const Vang::Windowing::Window& getWindow() const;
	Vang::gfx::GraphicsAPI& getGraphicsAPI();
	const Vang::gfx::GraphicsAPI& getGraphicsAPI() const;
	Vang::Objects::Player& getPlayer();
	const Vang::Objects::Player& getPlayer() const;
	Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint>& getBlockManager();
	const Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint>& getBlockManager() const;
	Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint>& getItemManager();
	const Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint>& getItemManager() const;
	Vang::Modding::ModManager& getModManager();
	const Vang::Modding::ModManager& getModManager() const;

	void initialize();

	void pushLayer(Vang::Utility::Layers::Layer* layer);
	void pushOverlay(Vang::Utility::Layers::Layer* overlay);

	void update();

	void toClose();
	bool getToClose();

	void onEvent(Vang::Windowing::Event& e);

private:
	void cleanup();

	std::string m_applicationName;
	bool m_toClose;
	Vang::Utility::Layers::LayerStack m_layerStack;

	std::unique_ptr<Vang::Windowing::Window> m_window;
	std::unique_ptr<Vang::gfx::GraphicsAPI> m_graphicsAPI;
	Vang::Objects::Player m_player;
	Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint> m_blockManager;
	Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint> m_itemManager;
	Vang::Modding::ModManager m_modManager;

	VangInst(std::string_view applicationName = "");
	~VangInst()							 = default;
	VangInst(const VangInst&)			 = delete;
	VangInst(VangInst&&)				 = delete;
	VangInst& operator=(const VangInst&) = delete;
	VangInst& operator=(VangInst&&)		 = delete;
};