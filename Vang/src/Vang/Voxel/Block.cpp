#include "Block.h"

namespace Vang {

	Block::Block(const BlockBlueprint& blockBlueprint)
		: Item{blockBlueprint} {}

	Block::Block(const BlockBlueprint& blockBlueprint, uint32_t amount)
		: Item{blockBlueprint, amount} {}

}