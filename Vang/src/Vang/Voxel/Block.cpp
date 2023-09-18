#include "Block.h"

namespace Vang::Inventory {

	Block::Block(const Vang::Blueprints::BlockBlueprint& blockBlueprint)
		: Item{blockBlueprint} {}

	Block::Block(const Vang::Blueprints::BlockBlueprint& blockBlueprint, uint32_t amount)
		: Item{blockBlueprint, amount} {}

}