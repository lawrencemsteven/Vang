#pragma once

#include "Usability.h"

namespace Vang {

	class Unusable : public Usability {
	public:
		void use(Item& item) const override;
		UsabilityType getType() const override;
	};

}