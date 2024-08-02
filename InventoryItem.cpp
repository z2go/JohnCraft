#include "InventoryItem.h"

InventoryItem::InventoryItem() {
	type = -1;
}

InventoryItem::InventoryItem(int t, int s) {
	type = t;
	stack = s;

	switch (type) {
	case 0:
		name = "Wooden Pickaxe";
		description = "Not very durable";
		toolType = 'p';
		toolMult = 2;
		maxStack = 1;
		break;

	case 1:
		name = "Stone";
		description = "Trusty stone";
		blockType = 1;
		break;

	case 2:
		name = "Stone Cap";
		description = "No Cap ONG";
		armorType = 'h';
		maxStack = 1;
		damageReduction = 1;
		break;
	case 3:
		name = "Stone Pickaxe";
		description = "Best in class";
		toolType = 'p';
		toolMult = 3;
		maxStack = 1;
		break;
	case 4:
		name = "Spear";
		description = "almost as long as my";
		damage = 4;
		maxStack = 1;
		break;
	case 5:
		name = "Stone Chestplate";
		description = "Rock solid";
		armorType = 'c';
		maxStack = 1;
		damageReduction = 1;
		break;
	case 6:
		name = "Wood";
		description = "Its mine btw";
		blockType = 2;
		break;
	case 7:
		name = "Stone Shoes";
		description = "Lit kicks";
		armorType = 'b';
		maxStack = 1;
		damageReduction = 1;
		break;
	case 8:
		name = "Stone Pants";
		description = "Me pantaloons";
		armorType = 'p';
		maxStack = 1;
		damageReduction = 1;
		break;
	case 9:
		name = "Planks";
		description = "Worse than wood";
		//Bruh Make a Block for dis
		break;
	case 10:
		name = "Stick";
		description = "Just a regular stick";
		break;
	case 11:
		name = "Workbench";
		description = "Forged by John himself";
		blockType = 8;
	}
	

		
}