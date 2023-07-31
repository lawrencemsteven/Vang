#include "Mod.h"

namespace Vang {

	Mod::Mod(std::string name)
		: m_name{std::move(name)} {}

	bool Mod::operator==(Mod& othermod) {
		return m_name == othermod.getName();
	}

	const std::string& Mod::getName() const {
		return m_name;
	}

}