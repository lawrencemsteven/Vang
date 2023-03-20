#pragma once

#include "Vang/Window/Window.h"
#include "Vang/GraphicsAPI/GraphicsAPI.h"

class VangInst {
public:
	static VangInst& Get(std::string_view applicationName = "");

	void beginFrame();
	void endFrame();

	void cleanup();

private:
	std::string_view m_applicationName;

	std::shared_ptr<Vang::Window> m_window;
	std::shared_ptr<Vang::GraphicsAPI> m_graphicsAPI;

	VangInst();
	VangInst(std::string_view applicationName);
	void operator=(const VangInst&) = delete;
};