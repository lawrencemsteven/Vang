#include "Item.h"

#include "Usability/Unusable.h"

namespace Vang {

	Item::Item(const std::string& name)
		: m_name{std::move(name)} {
		m_amount	= 1;
		m_maxStack	= 1;
		m_usability = std::make_unique<Unusable>();
	}

	Item::Item(const std::string& name, uint32_t amount, uint32_t maxStack)
		: Item{name} {
		m_amount   = amount;
		m_maxStack = maxStack;
	}

	Item::Item(const std::string& name, std::unique_ptr<Usability> usability)
		: Item{name} {
		m_usability = std::move(usability);
	}

	Item::Item(const std::string& name, uint32_t amount, uint32_t maxStack,
			   std::unique_ptr<Usability> usability)
		: Item{name, amount, maxStack} {
		m_usability = std::move(usability);
	}

	void Item::use() {
		m_usability->use(*this);
	}

	const std::string& Item::getName() const {
		return m_name;
	}
}