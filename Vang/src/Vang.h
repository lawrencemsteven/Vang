#pragma once

#include "Vang/Utility/Logging/Log.h"

class VangInst {
public:
	static VangInst& Get(std::string_view applicationName = "");

	void beginFrame();
	void endFrame();

	void cleanup();

private:
	std::string_view m_applicationName;

	VangInst() = delete;
	VangInst(std::string_view applicationName);
	void operator=(const VangInst&) = delete;
};