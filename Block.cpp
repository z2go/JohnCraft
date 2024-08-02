#include "Block.h"


using namespace std;
Block::Block(int xPos, int yPos, int blockType){
	gridPosition.x = xPos;
	gridPosition.y = yPos;
	type = blockType;

	switch (type) {
	case 0: //Grass
		break;

	case 1://Stone
		isWalkable = false;
		toughness = 10;
		bestTool = 'p';
		replaceable = false;
		isBreakable = true;
		itemType = 1;
		break;
	case 2://Tree
		isWalkable = false;
		toughness = 5;
		bestTool = 'a';
		replaceable = false;
		isBreakable = true;
		itemType = 6;
		break;
	case 3://Water
		speedMult = 0.5f;
		replaceable = false;
		break;
	case 4: //Pit
		replaceable = false;
		break;
	case 5: //Dark Walkway
		replaceable = false;
		break;
	case 6: //Lava Wall
		isWalkable = false;
		replaceable = false;
		break;
	case 7: //Lava
		speedMult = 0.33f;
		replaceable = false;
		break;
	case 8: //Workbench
		isWalkable = false;
		toughness = 5;
		bestTool = 'a';
		replaceable = false;
		isBreakable = true;
		itemType = 11;
		break;
	}
}
Block::Block() {

}

FloatRect Block::getPosition()
{
	return blockShape.getGlobalBounds();
}
RectangleShape Block::getShape() {
	return blockShape;
}

void Block::update() {
	screenPosition.x = gridPosition.x * 32 - 800;
	screenPosition.y = gridPosition.y * 32 - 450;
	blockShape.setPosition(screenPosition);
}

int Block::getBreakingAnimation() {
	//cout << breakingForce << " " << toughness << endl;
	return floor((float)breakingForce / toughness * 9) - 1;
}



