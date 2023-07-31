#include "ModManager.h"

namespace Vang {

	void ModManager::addMod(Mod& mod) {
		m_allMods.push_back(std::move(mod));
	}
}