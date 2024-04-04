#pragma once

#include "BlockBlueprint.h"
#include "Vang/Items/Item.h"

namespace Vang::Inventory {

	class Block : public Item {
	public:
		Block(const Vang::Blueprints::BlockBlueprint& blockBlueprint);
		Block(const Vang::Blueprints::BlockBlueprint& blockBlueprint, uint32_t amount);
	};

}