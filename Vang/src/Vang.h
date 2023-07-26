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
#	define VANG_CURRENT_WINDOW Vang::WindowGLFW
#endif

#include "Vang/GraphicsAPI/Generic/GraphicsAPI.h"
#include "Vang/Utility/Events/Event.h"
#include "Vang/Utility/Events/MouseEvent.h"
#include "Vang/Utility/Layers/LayerStack.h"
#include "Vang/Utility/Player/Player.h"
#include "Vang/Utility/Time/Time.h"
#include "Vang/Window/Window.h"

class VangInst {
public:
	static VangInst& Get(const std::string& applicationName = "");

	const std::string& getApplicationName();

	Vang::Window& getWindow();
	const Vang::Window& getWindow() const;
	Vang::gfx::GraphicsAPI& getGraphicsAPI();
	const Vang::gfx::GraphicsAPI& getGraphicsAPI() const;
	Vang::Player& getPlayer();
	const Vang::Player& getPlayer() const;

	void initialize();

	void pushLayer(Vang::Layer* layer);
	void pushOverlay(Vang::Layer* overlay);

	void update();

	void toClose();
	bool getToClose();

	void onEvent(Vang::Event& e);

private:
	void cleanup();

	std::string m_applicationName;
	bool m_toClose;
	Vang::LayerStack m_layerStack;

	std::unique_ptr<Vang::Window> m_window;
	std::unique_ptr<Vang::gfx::GraphicsAPI> m_graphicsAPI;
	std::unique_ptr<Vang::Player> m_player;

	VangInst(std::string_view applicationName = "");
	~VangInst()							 = default;
	VangInst(const VangInst&)			 = delete;
	VangInst(VangInst&&)				 = delete;
	VangInst& operator=(const VangInst&) = delete;
	VangInst& operator=(VangInst&&)		 = delete;
};