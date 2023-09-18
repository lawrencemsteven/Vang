#include "UniverseManager.h"


namespace Vang::Voxel::UniverseManager {

	static Universe s_currentUniverse;

	const Universe& createUniverse(const std::string& seed) {
		s_currentUniverse = Universe{seed};
		return s_currentUniverse;
	}

	const Universe& getCurrentUniverse() {
		return s_currentUniverse;
	}

}