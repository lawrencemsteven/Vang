#pragma once

#include "Vang/Window/Window.h"
#include "Vang/GraphicsAPI/Generic/GraphicsAPI.h"
#include "Vang/Utility/Player/Player.h"

class VangInst {
public:
	static VangInst& Get(std::string_view applicationName = "");

	std::string_view getApplicationName();

	Vang::Window& getWindow();
	const Vang::Window& getWindow() const;
	Vang::gfx::GraphicsAPI& getGraphicsAPI();
	const Vang::gfx::GraphicsAPI& getGraphicsAPI() const;
	Vang::Player& getPlayer();
	const Vang::Player& getPlayer() const;

	void initialize();

	void beginFrame();
	void endFrame();

	void toClose();
	bool getToClose();

private:
	void cleanup();

	std::string_view m_applicationName;
	bool m_toClose;

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