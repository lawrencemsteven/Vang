#pragma once

#ifdef VANG_GRAPHICSAPI_VULKAN
#	include "Vang/GraphicsAPI/GraphicsVulkan/GraphicsVulkan.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::Vulkan::GraphicsVulkan
#elif VANG_GRAPHICSAPI_OPENGL
#	include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::OpenGL::GraphicsOpenGL
#else
#	include "Vang/GraphicsAPI/GraphicsOpenGL/GraphicsOpenGL.h"
#	define VANG_CURRENT_GRAPHICSAPI Vang::gfx::OpenGL::GraphicsOpenGL
#endif

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
#define DEFAULT_FULLSCREEN false

#ifdef VANG_WINDOW_GLFW
#	include "Vang/Window/WindowGLFW/WindowGLFW.h"
#	define VANG_CURRENT_WINDOW Vang::Windowing::WindowGLFW
#	define VANG_CURRENT_WINDOW_INPUT Vang::Input::GLFWInputCache
#else
#	include "Vang/Window/WindowGLFW/WindowGLFW.h"
#	define VANG_CURRENT_WINDOW Vang::Windowing::WindowGLFW
#	define VANG_CURRENT_WINDOW_INPUT Vang::Input::GLFWInputCache
#endif

#include "Vang/GraphicsAPI/Generic/GraphicsAPI.h"
#include "Vang/Items/BlockBlueprint.h"
#include "Vang/Items/ItemBlueprint.h"
#include "Vang/Modding/ModManager.h"
#include "Vang/Utility/BlueprintContainer/BlueprintContainer.h"
#include "Vang/Utility/Entities/EntityManager.h"
#include "Vang/Utility/Events/Event.h"
#include "Vang/Utility/Events/EventHandler.h"
#include "Vang/Utility/Events/MouseEvent.h"
#include "Vang/Utility/FileIO/FileIO.h"
#include "Vang/Utility/Layers/LayerStack.h"
#include "Vang/Utility/Lights/LightManager.h"
#include "Vang/Utility/Player/Player.h"
#include "Vang/Utility/Structures/Structure.h"
#include "Vang/Utility/Time/Time.h"
#include "Vang/Utility/VMath/VMath.h"
#include "Vang/Voxel/Universe.h"
#include "Vang/Window/Window.h"

namespace Vang {
	extern void initialize();
	extern bool getRunning();
	extern void update();
	extern void close();

	extern const std::string& getApplicationName();
	extern Vang::Windowing::Window& getWindow();
	extern Vang::gfx::GraphicsAPI& getGraphicsAPI();
	extern Vang::Objects::Player& getPlayer();
	extern Vang::Blueprints::BlueprintContainer<Vang::Blueprints::BlockBlueprint>&
	getBlockManager();
	extern Vang::Blueprints::BlueprintContainer<Vang::Blueprints::ItemBlueprint>& getItemManager();
	extern Vang::Modding::ModManager& getModManager();
	extern Vang::Utility::Layers::LayerStack& getLayerStack();
	extern Vang::Utility::Events::EventHandler& getEventHandler();
	extern Vang::Input::InputCache& getInputCache();
	extern Vang::Voxel::World& getCurrentWorld();
	extern Vang::Utility::EntityManager& getEntityManager();
	extern Vang::Utility::LightManager& getLightManager();
};