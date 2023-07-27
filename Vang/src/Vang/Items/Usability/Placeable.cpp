#include "Placeable.h"

#include "Vang/Items/Item.h"

void Vang::Placeable::use(Item& item) {
	VANG_INFO("PLACE ITEM!");
	VANG_INFO(item.getName());
}