#include "ItemBlueprint.h"

#include "Usability/Unusable.h"

namespace Vang {

	ItemBlueprint::ItemBlueprint(Mod& mod, std::string technicalName,
								 std::string displayName)
		: m_mod{mod},
		  m_technicalName{std::move(technicalName)},
		  m_displayName{std::move(displayName)} {
		m_maxStack	= 1;
		m_usability = std::make_unique<Unusable>();
	}

	ItemBlueprint::ItemBlueprint(Mod& mod, std::string technicalName,
								 std::string displayName, uint32_t maxStack)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName)} {
		m_maxStack = maxStack;
	}

	ItemBlueprint::ItemBlueprint(Mod& mod, std::string technicalName,
								 std::string displayName, std::unique_ptr<Usability> usability)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName)} {
		setUsability(std::move(usability));
	}

	ItemBlueprint::ItemBlueprint(Mod& mod, std::string technicalName,
								 std::string displayName, uint32_t maxStack,
								 std::unique_ptr<Usability> usability)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName),
						maxStack} {
		setUsability(std::move(usability));
	}

	ItemBlueprint::ItemBlueprint(Mod& mod, std::string technicalName,
								 std::string displayName, UsabilityType usabilityType)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName)} {
		setUsability(usabilityType);
	}

	ItemBlueprint::ItemBlueprint(Mod& mod, std::string technicalName,
								 std::string displayName, uint32_t maxStack,
								 UsabilityType usabilityType)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName),
						maxStack} {
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

	Mod& ItemBlueprint::getMod() const {
		return m_mod;
	}

	const std::string& ItemBlueprint::getTechnicalName() const {
		return m_technicalName;
	}

	const std::string ItemBlueprint::getFullTechnicalName() const {
		return m_mod.getName() + "::" + m_technicalName;
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