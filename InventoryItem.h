#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class InventoryItem {
public:
	int type;
	int maxStack = 99;
	int durability = 0;
	int maxDurability = 0;
	int toolMult = 0;
	int stack = 0;
	int blockType = -1;
	char armorType = 'n';
	int damage = 1;
	int damageReduction = 0;
	
	char toolType = 'n';

	String name;
	String description;

	InventoryItem();
	InventoryItem(int type, int s);
	

	
};
