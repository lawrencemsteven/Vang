#pragma once

#include "BlockBlueprint.h"
#include "Vang/Items/Item.h"

namespace Vang {

	class Block : public Item {
	public:
		Block(const BlockBlueprint& blockBlueprint);
		Block(const BlockBlueprint& blockBlueprint, uint32_t amount);
	};

}