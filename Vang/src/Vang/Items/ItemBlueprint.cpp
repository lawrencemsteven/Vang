#include "ItemBlueprint.h"

#include "Usability/Unusable.h"

namespace Vang {

	ItemBlueprint::ItemBlueprint(const std::string& modName, std::string technicalName,
								 std::string displayName)
		: m_modName{m_modName},
		  m_technicalName{std::move(technicalName)},
		  m_displayName{std::move(displayName)} {
		m_maxStack	= 1;
		m_usability = std::make_unique<Unusable>();
	}

	ItemBlueprint::ItemBlueprint(const std::string& modName, std::string technicalName,
								 std::string displayName, uint32_t maxStack)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName)} {
		m_maxStack = maxStack;
	}

	ItemBlueprint::ItemBlueprint(const std::string& modName, std::string technicalName,
								 std::string displayName, std::unique_ptr<Usability> usability)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName)} {
		setUsability(std::move(usability));
	}

	ItemBlueprint::ItemBlueprint(const std::string& modName, std::string technicalName,
								 std::string displayName, uint32_t maxStack,
								 std::unique_ptr<Usability> usability)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName), maxStack} {
		setUsability(std::move(usability));
	}

	ItemBlueprint::ItemBlueprint(const std::string& modName, std::string technicalName,
								 std::string displayName, UsabilityType usabilityType)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName)} {
		setUsability(usabilityType);
	}

	ItemBlueprint::ItemBlueprint(const std::string& modName, std::string technicalName,
								 std::string displayName, uint32_t maxStack,
								 UsabilityType usabilityType)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName), maxStack} {
		m_usability = std::move(Usability::createFromType(usabilityType));
	}

	void ItemBlueprint::setMaxStack(uint32_t maxStack) {
		m_maxStack = maxStack;
	}

	void ItemBlueprint::setUsability(std::unique_ptr<Usability> usability) {
		m_usability = std::move(usability);
	}

	void ItemBlueprint::setUsability(UsabilityType usabilityType) {
		m_usability = std::move(Usability::createFromType(usabilityType));
	}

	const std::string& ItemBlueprint::getModName() const {
		return m_modName;
	}

	const std::string& ItemBlueprint::getTechnicalName() const {
		return m_technicalName;
	}

	const std::string ItemBlueprint::getFullTechnicalName() const {
		return m_modName + m_technicalName;
	}

	const std::string& ItemBlueprint::getDisplayName() const {
		return m_displayName;
	}

	uint32_t ItemBlueprint::getMaxStack() const {
		return m_maxStack;
	}

	Usability& ItemBlueprint::getUsability() const {
		return *m_usability;
	}

	UsabilityType ItemBlueprint::getUsabilityType() const {
		return m_usability->getType();
	}

}