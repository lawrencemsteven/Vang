#include "BlockBlueprint.h"

namespace Vang {

	BlockBlueprint::BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName),
						UsabilityType::Placeable} {}

	BlockBlueprint::BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
								   uint32_t maxStack)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName), maxStack,
						UsabilityType::Placeable} {}

	BlockBlueprint::BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
								   std::unique_ptr<Usability> usability)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName),
						std::move(usability)} {}

	BlockBlueprint::BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
								   uint32_t maxStack, std::unique_ptr<Usability> usability)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName), maxStack,
						std::move(usability)} {}

	BlockBlueprint::BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
								   UsabilityType usabilityType)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName), usabilityType} {}

	BlockBlueprint::BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
								   uint32_t maxStack, UsabilityType usabilityType)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName), maxStack,
						usabilityType} {}

}