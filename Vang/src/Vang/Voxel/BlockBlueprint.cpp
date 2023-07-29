#include "BlockBlueprint.h"

namespace Vang {

	BlockBlueprint::BlockBlueprint(const std::string& modName, std::string technicalName,
								   std::string displayName)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName),
						UsabilityType::Placeable} {}

	BlockBlueprint::BlockBlueprint(const std::string& modName, std::string technicalName,
								   std::string displayName, uint32_t maxStack)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName), maxStack,
						UsabilityType::Placeable} {}

	BlockBlueprint::BlockBlueprint(const std::string& modName, std::string technicalName,
								   std::string displayName, std::unique_ptr<Usability> usability)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName),
						std::move(usability)} {}

	BlockBlueprint::BlockBlueprint(const std::string& modName, std::string technicalName,
								   std::string displayName, uint32_t maxStack,
								   std::unique_ptr<Usability> usability)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName), maxStack,
						std::move(usability)} {}

	BlockBlueprint::BlockBlueprint(const std::string& modName, std::string technicalName,
								   std::string displayName, UsabilityType usabilityType)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName), usabilityType} {}

	BlockBlueprint::BlockBlueprint(const std::string& modName, std::string technicalName,
								   std::string displayName, uint32_t maxStack,
								   UsabilityType usabilityType)
		: ItemBlueprint{modName, std::move(technicalName), std::move(displayName), maxStack,
						usabilityType} {}

}