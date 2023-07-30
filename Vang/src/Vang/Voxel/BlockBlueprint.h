#pragma once

#include "Vang/Items/ItemBlueprint.h"

// TODO: Some way to define a texture? Maybe a texture is just a number corresponding to the surface
// shader?
namespace Vang {

	class BlockBlueprint : public ItemBlueprint {
	public:
		BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName);
		BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					   uint32_t maxStack);
		BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					   std::unique_ptr<Usability> usability);
		BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					   uint32_t maxStack, std::unique_ptr<Usability> usability);
		BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					   UsabilityType usabilityType);
		BlockBlueprint(Mod& mod, std::string technicalName, std::string displayName,
					   uint32_t maxStack, UsabilityType usabilityType);
	};

}