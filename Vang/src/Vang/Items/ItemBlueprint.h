#pragma once

#include "Usability/Usability.h"
#include "Vang/Modding/Mod.h"

namespace Vang::Blueprints {

	class ItemBlueprint {
	public:
		ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName);
		ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					  uint32_t maxStack);
		ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					  std::unique_ptr<Vang::Inventory::Usability> usability);
		ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					  uint32_t maxStack, std::unique_ptr<Vang::Inventory::Usability> usability);
		ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					  Vang::Inventory::UsabilityType usabilityType);
		ItemBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					  uint32_t maxStack, Vang::Inventory::UsabilityType usabilityType);

		void setMaxStack(uint32_t maxStack);
		void setUsability(std::unique_ptr<Vang::Inventory::Usability> usability);
		void setUsability(Vang::Inventory::UsabilityType usbilityType);

		Vang::Modding::Mod& getMod() const;
		const std::string& getTechnicalName() const;
		const std::string& getDisplayName() const;
		const std::string getFullTechnicalName() const;
		uint32_t getMaxStack() const;
		Vang::Inventory::Usability& getUsability() const;
		Vang::Inventory::UsabilityType getUsabilityType() const;

	protected:
		Vang::Modding::Mod& m_mod;
		const std::string m_technicalName;
		const std::string m_displayName;
		uint32_t m_maxStack{1};
		std::unique_ptr<Vang::Inventory::Usability> m_usability;
	};

}