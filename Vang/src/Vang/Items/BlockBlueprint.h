#pragma once

#include "Vang/Items/ItemBlueprint.h"

// TODO: Some way to define a texture? Maybe a texture is just a number corresponding to the surface
// shader?
namespace Vang::Blueprints {

	class BlockBlueprint : public ItemBlueprint {
	public:
		BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName);
		BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					   uint32_t maxStack);
		BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					   std::unique_ptr<Vang::Inventory::Usability> usability);
		BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					   uint32_t maxStack, std::unique_ptr<Vang::Inventory::Usability> usability);
		BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					   Vang::Inventory::UsabilityType usabilityType);
		BlockBlueprint(Vang::Modding::Mod& mod, std::string technicalName, std::string displayName,
					   uint32_t maxStack, Vang::Inventory::UsabilityType usabilityType);
	};

}