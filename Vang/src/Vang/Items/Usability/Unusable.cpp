#include "Unusable.h"

namespace Vang::Inventory {

	void Unusable::use(Item& item) const {}

	UsabilityType Unusable::getType() const {
		return UsabilityType::Unusable;
	}

}