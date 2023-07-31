#pragma once

#include "Mod.h"

namespace Vang {

	class ModManager {
	public:
		bool initialize();
		bool deinitialize();

		void addMod(Mod& mod);
		void removeMod(Mod& mod);

	private:
		std::vector<Mod> m_allMods;
		bool m_initialized;
	};

}