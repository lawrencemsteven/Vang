#pragma once

#include "Usability.h"

namespace Vang {

	class Unusable : public Usability {
	public:
		void use(Item& item) override;
		UsabilityType getType() const override;
	};

}