#include "Placeable.h"

#include "Vang/Items/Item.h"

namespace Vang {

	void Placeable::use(Item& item) const {
		VANG_INFO("PLACE ITEM!");
		VANG_INFO(item.getBlueprint().getFullTechnicalName());
	}

	UsabilityType Placeable::getType() const {
		return UsabilityType::Placeable;
	}

}