#include "Unusable.h"

namespace Vang {

	void Unusable::use(Item& item) {}

	UsabilityType Unusable::getType() const {
		return UsabilityType::Unusable;
	}

}