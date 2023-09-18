#pragma once

#include "Universe.h"

namespace Vang::Voxel::UniverseManager {

	const Universe& createUniverse(const std::string& seed);

	const Universe& getCurrentUniverse();

}