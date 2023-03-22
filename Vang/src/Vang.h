#pragma once

#include "Vang/Window/Window.h"
#include "Vang/GraphicsAPI/GraphicsAPI.h"

class VangInst {
public:
	static VangInst& Get(std::string_view applicationName = "");

	std::string_view getApplicationName();

	Vang::Window& getWindow();
	const Vang::Window& getWindow() const;
	Vang::GraphicsAPI& getGraphicsAPI();
	const Vang::GraphicsAPI& getGraphicsAPI() const;

	void beginFrame();
	void endFrame();

	void toClose();
	bool getToClose();

private:
	void cleanup();

	std::string_view m_applicationName;
	bool m_toClose;

	std::unique_ptr<Vang::Window> m_window;
	std::unique_ptr<Vang::GraphicsAPI> m_graphicsAPI;

	VangInst(std::string_view applicationName = "");
	~VangInst() = default;
	VangInst(const VangInst&)		= delete;
	VangInst(VangInst&&)			= delete;
	VangInst& operator=(const VangInst&) = delete;
	VangInst& operator=(VangInst&&)		= delete;
};