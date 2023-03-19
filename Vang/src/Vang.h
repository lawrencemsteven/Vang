#pragma once

#include "Vang/Utility/Logging/Log.h"

class VangInst {
public:
	VangInst& Get(std::string_view applicationName = "");

private:
	std::string_view m_applicationName;

	VangInst() = delete;
	VangInst(std::string_view applicationName);
	VangInst(const VangInst&)		= delete;
	VangInst(VangInst&&)			= delete;
	void operator=(const VangInst&) = delete;
	void operator=(VangInst&&)		= delete;
};