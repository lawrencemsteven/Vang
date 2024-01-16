#pragma once

#include "Universe.h"

namespace Vang::Voxel::UniverseManager {

	const std::shared_ptr<Universe> createUniverse(const std::string& seed);

	const std::shared_ptr<Universe> getCurrentUniverse();

}