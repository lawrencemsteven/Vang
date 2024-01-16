#include "UniverseManager.h"


namespace Vang::Voxel::UniverseManager {

	static std::shared_ptr<Universe> s_currentUniverse;

	const std::shared_ptr<Universe> createUniverse(const std::string& seed) {
		s_currentUniverse = std::make_shared<Universe>(seed);
		return s_currentUniverse;
	}

	const std::shared_ptr<Universe> getCurrentUniverse() {
		return s_currentUniverse;
	}

}