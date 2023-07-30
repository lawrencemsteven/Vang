#include "Mod.h"

namespace Vang {

	Mod::Mod(std::string name)
		: m_name{std::move(name)} {}

	const std::string& Mod::getName() const {
		return m_name;
	}

}