#pragma once

#include "Usability/Usability.h"

namespace Vang {

	class ItemBlueprint {
	public:
		ItemBlueprint(const std::string& modName, std::string technicalName,
					  std::string displayName);
		ItemBlueprint(const std::string& modName, std::string technicalName,
					  std::string displayName, uint32_t maxStack);
		ItemBlueprint(const std::string& modName, std::string technicalName,
					  std::string displayName, std::unique_ptr<Usability> usability);
		ItemBlueprint(const std::string& modName, std::string technicalName,
					  std::string displayName, uint32_t maxStack,
					  std::unique_ptr<Usability> usability);
		ItemBlueprint(const std::string& modName, std::string technicalName,
					  std::string displayName, UsabilityType usabilityType);
		ItemBlueprint(const std::string& modName, std::string technicalName,
					  std::string displayName, uint32_t maxStack, UsabilityType usabilityType);

		void setMaxStack(uint32_t maxStack);
		void setUsability(std::unique_ptr<Usability> usability);
		void setUsability(UsabilityType usbilityType);

		const std::string& getModName() const;
		const std::string& getTechnicalName() const;
		const std::string& getDisplayName() const;
		const std::string getFullTechnicalName() const;
		uint32_t getMaxStack() const;
		Usability& getUsability() const;
		UsabilityType getUsabilityType() const;

	protected:
		const std::string& m_modName;
		const std::string m_technicalName;
		const std::string m_displayName;
		uint32_t m_maxStack{1};
		std::unique_ptr<Usability> m_usability;
	};

}