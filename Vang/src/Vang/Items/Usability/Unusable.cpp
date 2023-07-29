#include "Unusable.h"

namespace Vang {

	void Unusable::use(Item& item) const {}

	UsabilityType Unusable::getType() const {
		return UsabilityType::Unusable;
	}

}