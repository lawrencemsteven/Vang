#include "BlockBlueprint.h"

namespace Vang::Blueprints {

	BlockBlueprint::BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName),
						Vang::Inventory::UsabilityType::Placeable} {}

	BlockBlueprint::BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
								   uint32_t maxStack)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName), maxStack,
						Vang::Inventory::UsabilityType::Placeable} {}

	BlockBlueprint::BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
								   std::unique_ptr<Vang::Inventory::Usability> usability)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName),
						std::move(usability)} {}

	BlockBlueprint::BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
								   uint32_t maxStack, std::unique_ptr<Vang::Inventory::Usability> usability)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName), maxStack,
						std::move(usability)} {}

	BlockBlueprint::BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
								   Vang::Inventory::UsabilityType usabilityType)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName), usabilityType} {}

	BlockBlueprint::BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
								   uint32_t maxStack, Vang::Inventory::UsabilityType usabilityType)
		: ItemBlueprint{mod, std::move(technicalName), std::move(displayName), maxStack,
						usabilityType} {}

}