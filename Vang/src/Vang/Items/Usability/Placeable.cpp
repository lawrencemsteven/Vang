#include "Placeable.h"

#include "Vang/Items/Item.h"

namespace Vang {

	void Placeable::use(Item& item) {
		VANG_INFO("PLACE ITEM!");
		VANG_INFO(item.getName());
	}

	UsabilityType Placeable::getType() const {
		return UsabilityType::Placeable;
	}

}