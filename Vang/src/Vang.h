#pragma once

#ifdef VANG_GRAPHICSAPI_VULKAN
#	include "Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::Vulkan::GraphicsVulkan
#elif VANG_GRAPHICSAPI_OPENGL
#	include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::OpenGL::GraphicsOpenGL
#endif

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080

#ifdef VANG_WINDOW_GLFW
#	include "Vang/Window/WindowGLFW/WindowGLFW.h"
#	define VANG_CURRENT_WINDOW Vang::Windowing::WindowGLFW
#endif

#include "Vang/GraphicsAPI/Generic/GraphicsAPI.h"
#include "Vang/Items/ItemBlueprint.h"
#include "Vang/Modding/ModManager.h"
#include "Vang/Utility/BlueprintContainer/BlueprintContainer.h"
#include "Vang/Utility/Events/Event.h"
#include "Vang/Utility/Events/EventHandler.h"
#include "Vang/Utility/Events/MouseEvent.h"
#include "Vang/Utility/Layers/LayerStack.h"
#include "Vang/Utility/Player/Player.h"
#include "Vang/Utility/Time/Time.h"
#include "Vang/Voxel/BlockBlueprint.h"
#include "Vang/Voxel/Universe.h"
#include "Vang/Window/Window.h"

namespace Vang {
	bool getRunning();
	void update();
	void close();

	const std::string& getApplicationName();
	Vang::Windowing::Window& getWindow();
	Vang::gfx::GraphicsAPI& getGraphicsAPI();
	Vang::Objects::Player& getPlayer();
	Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint>& getBlockManager();
	Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint>& getItemManager();
	Vang::Modding::ModManager& getModManager();
	Vang::Utility::Layers::LayerStack& getLayerStack();
	Vang::Windowing::EventHandler& getEventHandler();
};