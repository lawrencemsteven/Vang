#include "Vang.h"

VangInst& VangInst::Get(std::string_view applicationName) {
	static VangInst s_vangInst{applicationName};
	return s_vangInst;
}

VangInst::VangInst(std::string_view applicationName)
	: m_applicationName{applicationName} {}