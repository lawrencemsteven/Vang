#include "Item.h"

#include "Usability/Unusable.h"

namespace Vang::Inventory {

	Item::Item(const Vang::Blueprints::ItemBlueprint& itemBlueprint)
		: m_blueprint{itemBlueprint} {
	}

	Item::Item(const Vang::Blueprints::ItemBlueprint& itemBlueprint, uint32_t amount)
		: m_blueprint{itemBlueprint},
		  m_amount{amount} {}

	void Item::use() {
		m_blueprint.getUsability().use(*this);
	}

	void Item::setAmount(uint32_t amount) {
		m_amount = amount;
	}

	void Item::incrementAmount(int32_t amount) {
		m_amount = static_cast<uint32_t>(std::clamp(static_cast<int32_t>(m_amount) + amount, 0,
													static_cast<int32_t>(m_blueprint.getMaxStack())));
	}

	const Vang::Blueprints::ItemBlueprint& Item::getBlueprint() const {
		return m_blueprint;
	}

	uint32_t Item::getAmount() const {
		return m_amount;
	}

}