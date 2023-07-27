#pragma once

#include "Usability.h"

namespace Vang {

	class Unusable : public Usability {
	public:
		Unusable() = default;
		~Unusable() = default;

		void use(Item& item) override;
	};

}