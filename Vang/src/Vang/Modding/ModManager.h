#pragma once

#include "Mod.h"

namespace Vang::Modding {

	class ModManager {
	public:
		ModManager()							 = default;
		~ModManager()							 = default;
		ModManager(const ModManager&)			 = delete;
		ModManager(ModManager&&)				 = delete;
		ModManager& operator=(const ModManager&) = delete;
		ModManager& operator=(ModManager&&)		 = delete;
		bool initialize();
		bool deinitialize();

		void addMod(Mod& mod);
		void removeMod(Mod& mod);

	private:
		std::vector<Mod> m_allMods;
		bool m_initialized{false};
	};

}