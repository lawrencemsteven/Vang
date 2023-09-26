#include "Usability.h"

#include "Unusable.h"
#include "Placeable.h"

namespace Vang::Inventory {

	std::unique_ptr<Usability> Usability::createFromType(UsabilityType usabilityType) {
		switch (usabilityType) {
			case UsabilityType::Unusable: return std::make_unique<Unusable>();
			case UsabilityType::Placeable: return std::make_unique<Placeable>();
			default: VANG_FATAL("USABILITY TYPE NOT SUPPORTED!"); return nullptr;
		}
	}

}