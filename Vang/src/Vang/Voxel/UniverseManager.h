#pragma once

#include "Universe.h"

namespace Vang::UniverseManager {

	const Universe& createUniverse(const std::string& seed);

	const Universe& getCurrentUniverse();

}