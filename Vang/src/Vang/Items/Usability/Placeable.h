#pragma once

#include "Usability.h"

namespace Vang::Inventory {

	class Placeable : public Usability {
	public:
		void use(Item& item) const override;
		UsabilityType getType() const;
	};

}