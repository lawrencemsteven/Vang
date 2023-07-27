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
		setUsability(std::move(usability));
	}

	Item::Item(const std::string& name, uint32_t amount, uint32_t maxStack,
			   std::unique_ptr<Usability> usability)
		: Item{name, amount, maxStack} {
		setUsability(std::move(usability));
	}

	Item::Item(const std::string& name, UsabilityType usabilityType)
		: Item{name} {
		setUsability(usabilityType);
	}

	Item::Item(const std::string& name, uint32_t amount, uint32_t maxStack,
			   UsabilityType usabilityType)
		: Item{name, amount, maxStack} {
		setUsability(usabilityType);
	}

	void Item::use() {
		m_usability->use(*this);
	}

	void Item::setName(const std::string& name) {
		m_name = std::move(name);
	}

	void Item::setAmount(uint32_t amount) {
		m_amount = amount;
	}

	void Item::incrementAmount(int32_t amount) {
		m_amount = static_cast<uint32_t>(std::clamp(static_cast<int32_t>(m_amount) + amount, 0,
													static_cast<int32_t>(m_maxStack)));
	}

	void Item::setMaxStack(uint32_t maxStack) {
		m_maxStack = maxStack;
	}

	void Item::setUsability(std::unique_ptr<Usability> usability) {
		m_usability = std::move(usability);
	}

	void Item::setUsability(UsabilityType usbilityType) {
		m_usability = std::move(Usability::createFromType(usabilityType));
	}

	const std::string& Item::getName() const {
		return m_name;
	}

	uint32_t Item::getAmount() const {
		return m_amount;
	}
	uint32_t Item::getMaxStack() const {
		return m_maxStack;
	}
	Usability& Item::getUsability() {
		return *m_usability;
	}
	UsabilityType Item::getUsabilityType() const {
		return m_usability->getType();
	}
}