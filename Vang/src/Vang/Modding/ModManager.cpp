#include "ModManager.h"

namespace Vang::Modding {

	bool ModManager::initialize() {
		return true;
	}

	bool ModManager::deinitialize() {
		return true;
	}

	void ModManager::addMod(Mod& mod) {
		m_allMods.push_back(std::move(mod));
	}

	void ModManager::removeMod(Mod& mod) {}
}