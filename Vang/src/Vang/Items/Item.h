#pragma once

#include "ItemBlueprint.h"
#include "Usability/Usability.h"

namespace Vang::Inventory {

	class Item {
	public:
		Item(const Vang::Blueprints::ItemBlueprint& itemBlueprint);
		Item(const Vang::Blueprints::ItemBlueprint& itemBlueprint, uint32_t amount);

		void use();

		void setAmount(uint32_t amount);
		void incrementAmount(int32_t amount);

		const Vang::Blueprints::ItemBlueprint& getBlueprint() const;
		uint32_t getAmount() const;

	protected:
		const Vang::Blueprints::ItemBlueprint& m_blueprint;
		uint32_t m_amount{1};
	};

}