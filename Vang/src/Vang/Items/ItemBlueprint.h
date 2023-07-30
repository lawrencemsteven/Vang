#pragma once

#include "Usability/Usability.h"
#include "Vang/Modding/Mod.h"

namespace Vang {

	class ItemBlueprint {
	public:
		ItemBlueprint(Mod& mod, std::string technicalName, std::string displayName);
		ItemBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					  uint32_t maxStack);
		ItemBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					  std::unique_ptr<Usability> usability);
		ItemBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					  uint32_t maxStack, std::unique_ptr<Usability> usability);
		ItemBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					  UsabilityType usabilityType);
		ItemBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					  uint32_t maxStack, UsabilityType usabilityType);

		void setMaxStack(uint32_t maxStack);
		void setUsability(std::unique_ptr<Usability> usability);
		void setUsability(UsabilityType usbilityType);

		Mod& getMod() const;
		const std::string& getTechnicalName() const;
		const std::string& getDisplayName() const;
		const std::string getFullTechnicalName() const;
		uint32_t getMaxStack() const;
		Usability& getUsability() const;
		UsabilityType getUsabilityType() const;

	protected:
		Mod& m_mod;
		const std::string m_technicalName;
		const std::string m_displayName;
		uint32_t m_maxStack{1};
		std::unique_ptr<Usability> m_usability;
	};

}