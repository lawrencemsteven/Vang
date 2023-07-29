#pragma once

#include "ItemBlueprint.h"
#include "Usability/Usability.h"

namespace Vang {

	class Item {
	public:
		Item(const ItemBlueprint& itemBlueprint);
		Item(const ItemBlueprint& itemBlueprint, uint32_t amount);

		void use();

		void setAmount(uint32_t amount);
		void incrementAmount(int32_t amount);

		const ItemBlueprint& getBlueprint() const;
		uint32_t getAmount() const;

	protected:
		const ItemBlueprint& m_blueprint;
		uint32_t m_amount{1};
	};

}