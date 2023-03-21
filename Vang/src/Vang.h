#pragma once

#include "Vang/Window/Window.h"
#include "Vang/GraphicsAPI/GraphicsAPI.h"

class VangInst {
public:
	static VangInst& Get(std::string_view applicationName = "");

	std::string_view getApplicationName();

	void beginFrame();
	void endFrame();

	void toClose();
	bool getToClose();

private:
	void cleanup();

	std::string_view m_applicationName;
	bool m_toClose;

	std::shared_ptr<Vang::Window> m_window;
	std::shared_ptr<Vang::GraphicsAPI> m_graphicsAPI;

	VangInst();
	VangInst(std::string_view applicationName);
	VangInst(const VangInst&)		= delete;
	void operator=(const VangInst&) = delete;
};