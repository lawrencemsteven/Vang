#include "ItemBlueprint.h"

#include "Usability/Unusable.h"

namespace Vang::Blueprints {

	ItemBlueprint::ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName,
								 std::string displayName)
		: m_mod{mod},
		  m_technicalName{std::move(technicalName)},
		  m_displayName{std::move(displayName)} {
		m_maxStack	= 1;
		m_usability = std::make_unique<Vang::Inventory::Unusable>();
	}

	ItemBlueprint::ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName,
								 std::string displayName, uint32_t maxStack)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName)} {
		m_maxStack = maxStack;
	}

	ItemBlueprint::ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName,
								 std::string displayName, std::unique_ptr<Vang::Inventory::Usability> usability)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName)} {
		setUsability(std::move(usability));
	}

	ItemBlueprint::ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName,
								 std::string displayName, uint32_t maxStack,
								 std::unique_ptr<Vang::Inventory::Usability> usability)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName),
						maxStack} {
		setUsability(std::move(usability));
	}

	ItemBlueprint::ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName,
								 std::string displayName, Vang::Inventory::UsabilityType usabilityType)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName)} {
		setUsability(usabilityType);
	}

	ItemBlueprint::ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName,
								 std::string displayName, uint32_t maxStack,
								 Vang::Inventory::UsabilityType usabilityType)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName),
						maxStack} {
		m_usability = std::move(Vang::Inventory::Usability::createFromType(usabilityType));
	}

	void ItemBlueprint::setMaxStack(uint32_t maxStack) {
		m_maxStack = maxStack;
	}

	void ItemBlueprint::setUsability(std::unique_ptr<Vang::Inventory::Usability> usability) {
		m_usability = std::move(usability);
	}

	void ItemBlueprint::setUsability(Vang::Inventory::UsabilityType usabilityType) {
		m_usability = std::move(Vang::Inventory::Usability::createFromType(usabilityType));
	}

	Vang::Modding::Mod& ItemBlueprint::getMod() const {
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

	Vang::Inventory::Usability& ItemBlueprint::getUsability() const {
		return *m_usability;
	}

	Vang::Inventory::UsabilityType ItemBlueprint::getUsabilityType() const {
		return m_usability->getType();
	}

}