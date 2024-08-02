#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include "Player.h"
#include "Block.h"
#include <random>
#include "InventoryItem.h"
#include "FloorItem.h"
#include "Entity.h"
#include <iostream>

using namespace std;

const int worldSize = 100;

Player player = Player(800, 450);

Texture blockTexture;
Texture playerTexture;
Texture breakingTexture;
Texture inventoryTexture;
Texture selectedTexture;
Texture itemTexture;
Texture heartTexture;
Texture bossTexture;
Texture smallCraftTexture;
Texture bigCraftTexture;
Texture homeScreenTexture;

Sprite blockSprite[worldSize][worldSize];
Sprite bossBlockSprite[20][20];

Sprite playerSprite;
Sprite breakingSprite;
Sprite inventorySprite;
Sprite selectedSprite;
Sprite hotBarSprite;
Sprite offHandSprite;
Sprite armorSprite;
Sprite bossSprite;
Sprite smallCraftSprite;
Sprite bigCraftSprite;
Sprite homeScreenSprite;

vector<Sprite> itemSprites;

IntRect playerRect[12];
IntRect blockRect[9];
IntRect breakingRect[9];
IntRect inventoryRect;
IntRect hotbarRect;
IntRect armorRect;
IntRect offHandRect;
IntRect selectedRect;
IntRect itemRect[12];
IntRect heartRect[5];
IntRect bossRect[12];
IntRect smallCraftRect;
IntRect bigCraftRect;

RectangleShape playButton;
RectangleShape itemTextBox;

Text titleText;
Text playText;

Text itemNameText;

Block blocks[worldSize][worldSize];
Block bossBlocks[20][20];

sf::Vector2i mousePos;
sf::Vector2i blockSelected;
sf::Vector2i realMousePos;

int dimension = 0;
int slotSelected = 0;
int hotbarSlotPos[10];

Vector2f inventorySlotPos[50];
Vector2f armorSlotPos[4];
Vector2f heartPos[10];
Vector2f smallCraftPos[4];
Vector2f bigCraftPos[9];
Vector2f bigCraftResultPos;
Vector2f smallCraftResultPos;

int slotHover = 0;

int screenX = 1600;
int screenY = 900;

bool leftMouseClicked = false;
bool rightMouseClicked = false;

bool isBigCraft = false;

InventoryItem craftingGrid[3][3];

InventoryItem inventory[50];
InventoryItem hotbar[10];

InventoryItem armor[4];
InventoryItem offHand;

InventoryItem itemHeld = InventoryItem(-1,0);

InventoryItem cursorItem;

vector<FloorItem> floorItems;

InventoryItem craftedItem;

int playerSpeed;
int tickCount = 0;
int imgCount = 0;

float maxHealth = 10.0f;
float health = 10.00f;

bool inventoryShown = false;

int bossEdge = 6;
int bossMiddle = 5;

int bossBlockTypes[20][20] = {
	{bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossMiddle, bossEdge },
	{bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge, bossEdge }
};

vector<Entity> entities;

Font font;

sf::Clock c;

sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Final Project");

enum GameState {
	START, 
	ALIVE, 
	DEAD
};

GameState state = START;

void generateWorld() {
	//player.position.x = (rand() % worldSize * 96 - 192) + 96;
	int grassPlanted = 0;
	int wallsBuilt = 0;
	int treesPlanted = 0;
	int pebbles = 0;
	int rocks = 0;
	int boulders = 0;
	int riversBuilt = ceil(worldSize/100);

	vector<bool> riverIsVertical;
	vector<int> riverStart;
	vector<int> riverRadius;

	for (int i = 0; i < riversBuilt; i++) {
		riverIsVertical.push_back((bool)rand() % 2);
		riverStart.push_back((rand() % worldSize - 6) + 3);
		riverRadius.push_back(rand() % 2 + 2);
	}
	
	for (int i = 0; i < worldSize; i++) {
		for (int j = 0; j < worldSize; j++) {
			if (i == 0 or j == 0 or i == worldSize - 1 or j == worldSize - 1) {
				blocks[i][j] = Block(i, j, 6);
				wallsBuilt++;
			}
			else
			{
				blocks[i][j] = Block(i, j, 0);
				grassPlanted++;
			}
		}
	}
	cout << "Planted " << grassPlanted << " grass (1/7)" << endl;
	cout << "Erected " << wallsBuilt << " walls (2/7)" << endl;

	for (int i = 1; i < worldSize-1; i++) {
		for (int j = 1; j < worldSize-1; j++) {
			if (rand() % 64 == 0) {
				blocks[i][j] = Block(i, j, 2);
				treesPlanted++;
			}
		}
	}
	cout << "Grew " << treesPlanted << " trees (3/7)" << endl;

	for (int i = 1; i < worldSize - 1; i++) {
		for (int j = 1; j < worldSize - 1; j++) {
			if (rand() % 100 == 0) {
				blocks[i][j] = Block(i, j, 1);
				pebbles++;
			}
		}
	}

	cout << "Dropped " << pebbles << " pebbles (4/7)" << endl;

	for (int i = 1; i < worldSize - 1; i++) {
		for (int j = 1; j < worldSize - 1; j++) {
			if (rand() % 1000 == 0) {
				rocks++;
				for (int k = -1; k < 2; k++) {
					for (int l = -1; l < 2; l++) {
						if (i+k > 0 and j+l > 0 and i+k < worldSize-1 and j + l < worldSize-1)
						{
							blocks[i + k][j+l] = Block(i + k, j+l, 1);
							
						}
						
					}
				}
				
			}
		}
	}

	cout << "Uncovered " << rocks << " rocks (5/7)" << endl;
	for (int i = 1; i < worldSize - 1; i++) {
		for (int j = 1; j < worldSize - 1; j++) {
			if (rand() % 10000 == 0) {
				boulders++;
				for (int k = -2; k < 3; k++) {
					for (int l = -2; l < 3; l++) {
						if (i + k > 0 and j + l > 0 and i + k < worldSize - 1 and j + l < worldSize - 1)
						{
							if (k == 0 and l == 0) {
								blocks[i + k][j + l] = Block(i + k, j + l, 4);
							}
							else {
								blocks[i + k][j + l] = Block(i + k, j + l, 1);
							}
						}
					}
				}
			}
		}
	}

	cout << "Excavated " << boulders << " boulders (6/7)" << endl;

	for (int i = 0; i < riverIsVertical.size(); i++) {
		if (riverIsVertical.at(i)) {
			int riverX = (rand() % (worldSize - 12)) + 6;
			for (int j = riverX - riverRadius.at(i); j <= riverX + riverRadius.at(i); j++) {
				for (int k = 1; k < worldSize - 1; k++) {
					blocks[j][k] = Block(j, k, 3);
				}
			}
		}
		else
		{ 
			int riverY = (rand() % (worldSize - 12)) + 6;
			for (int j = riverY - riverRadius.at(i); j <= riverY + riverRadius.at(i); j++) {
				for (int k = 1; k < worldSize - 1; k++) {
					blocks[k][j] = Block(k, j, 3);
				}
			}
		}

	}

	cout << "Dug " << riversBuilt << " rivers (7/7)" << endl;
}

void loadAssets() {
	generateWorld();
	itemHeld = hotbar[0];


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			craftingGrid[i][j] = InventoryItem(-1, 0);
		}
	}

	for (int i = 0; i < 4; i++) {
		armorSlotPos[i].x = 240;
		armorSlotPos[i].y = 356 + i * 96;
	}

	for (int i = 0; i < 10; i++) {
		hotbarSlotPos[i] = 368 + i * 96;
	}

	for (int i = 0; i > 10; i++) {
		heartPos[i].x = i * 40 + 20;
		heartPos[i].y = 20;
	}

	for (int i = 0; i < 50; i++) {
		inventorySlotPos[i].x = (i % 10) * 96 + 368;
		inventorySlotPos[i].y = floor(i / 10) * 96 + 308;
	}

	for (int i = 0; i < 4; i++) {
		smallCraftPos[i].x = 106 + i % 2 * 96;
		smallCraftPos[i].y = 102 + floor(i / 2) * 96;
	}
	for (int i = 0; i < 9; i++) {
		bigCraftPos[i].x = 58 + i % 3 * 96;
		bigCraftPos[i].y = 54 + floor(i / 3) * 96;
	}

	smallCraftResultPos.x = 394;
	smallCraftResultPos.y = 150;

	bigCraftResultPos.x = 442;
	bigCraftResultPos.y = 150;
	for (int i = 0; i < 12; i++) {
		bossRect[i] = IntRect(i % 3 * 32, floor(i / 3) * 32, 32, 32);
		playerRect[i] = IntRect(i % 3 * 32, floor(i / 3) * 32, 32, 32);
		itemRect[i] = IntRect(i % 3 * 32, floor(i / 3) * 32, 32, 32);
	}
	for (int i = 0; i < 12; i++) {
		
	}
	for (int i = 0; i < 9; i++) {
		blockRect[i] = IntRect(i % 3 * 32, floor(i / 3) * 32, 32, 32);
	}
	for (int i = 0; i < 9; i++) {
		breakingRect[i] = IntRect(i % 3 * 32, floor(i / 3) * 32, 32, 32);
	}
	for (int i = 0; i < 2; i++) {
		itemRect[i] = IntRect(i % 2 * 32, floor(i / 2) * 32, 32, 32);
	}

	for (int i = 0; i < 5; i++) {
		heartRect[i] = IntRect(i * 16, 0, 16, 16);
	}


	hotbarRect = IntRect(0, 0, 160, 16);
	inventoryRect = IntRect(0, 0, 160, 80);
	armorRect = IntRect(0, 0, 16, 64);
	offHandRect = IntRect(0, 0, 16, 16);
	smallCraftRect = IntRect(0, 0, 64, 32);
	bigCraftRect = IntRect(0, 0, 80, 48);
	selectedRect = IntRect(0, 0, 32, 32);

	blockTexture.loadFromFile("Assets/blocks.png");
	
	for (int i = 0; i < worldSize; i++) {
		for (int j = 0; j < worldSize; j++) {

			blockSprite[i][j].setTexture(blockTexture);
			blockSprite[i][j].setTextureRect(blockRect[blocks[i][j].type]);
			blockSprite[i][j].setOrigin(16, 16);
			blockSprite[i][j].setScale(4, 4);
			blockSprite[i][j].setPosition(i * 128 - player.position.x + 1000, j * 128 - player.position.y + 1000);
		}
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			bossBlocks[i][j] = Block(i, j, bossBlockTypes[i][j]);
			bossBlockSprite[i][j].setTexture(blockTexture);

			bossBlockSprite[i][j].setTextureRect(blockRect[bossBlocks[i][j].type]);
			bossBlockSprite[i][j].setOrigin(16, 16);
			bossBlockSprite[i][j].setScale(4, 4);
			bossBlockSprite[i][j].setPosition(i * 128 - player.position.x + 1000, j * 128 - player.position.y + 1000);

		}
	}
	font.loadFromFile("Assets/Candal.ttf");

	homeScreenTexture.loadFromFile("Assets/home.png");

	homeScreenSprite.setTexture(homeScreenTexture);
	homeScreenSprite.setOrigin(0, 0);
	homeScreenSprite.setScale(1.21, 1.21);
	homeScreenSprite.setPosition(0, 0);

	breakingTexture.loadFromFile("Assets/breaking.png");

	breakingSprite.setTexture(breakingTexture);
	breakingSprite.setTextureRect(breakingRect[0]);
	breakingSprite.setOrigin(16, 16);
	breakingSprite.setScale(4, 4);
	breakingSprite.setPosition(player.position.x + 1000, player.position.y + 1000);


	playerTexture.loadFromFile("Assets/josh.png");

	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(playerRect[0]);
	playerSprite.setOrigin(16, 16);
	playerSprite.setScale(5, 5);
	playerSprite.setPosition(800, 450);

	smallCraftTexture.loadFromFile("Assets/smallCraft.png");

	smallCraftSprite.setTexture(smallCraftTexture);
	smallCraftSprite.setTextureRect(smallCraftRect);
	smallCraftSprite.setOrigin(32, 16);
	smallCraftSprite.setScale(6, 6);
	smallCraftSprite.setPosition(250, 150);

	bigCraftTexture.loadFromFile("Assets/bigCraft.png");

	bigCraftSprite.setTexture(bigCraftTexture);
	bigCraftSprite.setTextureRect(bigCraftRect);
	bigCraftSprite.setOrigin(40, 24);
	bigCraftSprite.setScale(6, 6);
	bigCraftSprite.setPosition(250, 150);

	inventoryTexture.loadFromFile("Assets/inventory.png");

	inventorySprite.setTexture(inventoryTexture);
	inventorySprite.setTextureRect(inventoryRect);
	inventorySprite.setOrigin(80, 40);
	inventorySprite.setScale(6, 6);
	inventorySprite.setPosition(800, 500);

	hotBarSprite.setTexture(inventoryTexture);
	hotBarSprite.setTextureRect(hotbarRect);
	hotBarSprite.setOrigin(80, 8);
	hotBarSprite.setScale(6, 6);
	hotBarSprite.setPosition(800, 840);

	armorSprite.setTexture(inventoryTexture);
	armorSprite.setTextureRect(armorRect);
	armorSprite.setOrigin(8, 32);
	armorSprite.setScale(6, 6);
	armorSprite.setPosition(240, 500);

	offHandSprite.setTexture(inventoryTexture);
	offHandSprite.setTextureRect(offHandRect);
	offHandSprite.setOrigin(8, 8);
	offHandSprite.setScale(6, 6);
	offHandSprite.setPosition(240, 840);

	selectedTexture.loadFromFile("Assets/selected.png");

	selectedSprite.setTexture(selectedTexture);
	selectedSprite.setTextureRect(selectedRect);
	selectedSprite.setOrigin(16, 16);
	selectedSprite.setScale(3, 3);
	selectedSprite.setPosition(800, 840);

	bossTexture.loadFromFile("Assets/jenil.png");

	bossSprite.setTexture(bossTexture);
	bossSprite.setOrigin(16, 16);
	bossSprite.setScale(5, 5);
	bossSprite.setPosition(player.position.x + 1000, player.position.y + 1000);

	itemTexture.loadFromFile("Assets/items.png");

	heartTexture.loadFromFile("Assets/heart.png");

	itemNameText.setFont(font);
	itemNameText.setFillColor(Color::Black);
	itemNameText.setCharacterSize(40);

	titleText.setFont(font);
	titleText.setOrigin(45, 50);
	titleText.setPosition(560, 100);
	titleText.setString("JohnCraft");
	titleText.setFillColor(Color::Black);
	titleText.setCharacterSize(100);

	playText.setFont(font);
	playText.setOrigin(45, 50);
	playText.setPosition(720, 780);
	playText.setString("Play");
	playText.setFillColor(Color::Black);
	playText.setCharacterSize(100);

	Vector2f playBoxBounds;
	playBoxBounds.x = 300;
	playBoxBounds.y = 150;

	playButton.setSize(playBoxBounds);
	playButton.setOrigin(playBoxBounds.x / 2, playBoxBounds.y / 2);
	playButton.setOutlineThickness(2);
	playButton.setOutlineColor(Color::Black);
	playButton.setFillColor(Color::Green);
	playButton.setPosition(800, 800);
	
}

bool checkValidPos(char direction) {

	bool checkUpLeft = false;
	bool checkUpRight = false;
	bool checkDownLeft = false;
	bool checkDownRight = false;

	if (direction == 'u') {
		checkUpLeft = true;
		checkUpRight = true;
	}
	else if (direction == 'd') {
		checkDownLeft = true;
		checkDownRight = true;
	}
	else if (direction == 'l') {
		checkUpLeft = true;
		checkDownLeft = true;
	}
	else if (direction == 'r') {
		checkUpRight = true;
		checkDownRight = true;
	}
	Vector2i checkPos;

	if (checkUpLeft) {
		checkPos.x = (player.position.x + 30 - 800 + (direction == 'u')) / 128;
		checkPos.y = (player.position.y + 10 - 450 + (direction == 'l')) / 128;
	}
	else if (checkDownRight) {
		checkPos.x = (player.position.x + 95 - 800 - (direction == 'd')) / 128;
		checkPos.y = (player.position.y + 130 - 450 - (direction == 'r')) / 128;
	}
	if (dimension == 0) {
		if (not blocks[checkPos.x][checkPos.y].isWalkable) {
			return false;
		}
	}
	else if (dimension == 1) {
		if (not bossBlocks[checkPos.x][checkPos.y].isWalkable) {
			return false;
		}
	}

	if (checkDownLeft) {
		checkPos.x = (player.position.x + 30 - 800 + (direction == 'd')) / 128;
		checkPos.y = (player.position.y + 130 - 450 - (direction == 'l')) / 128;
	}
	else if (checkUpRight) {
		checkPos.x = (player.position.x + 95 - 800 - (direction == 'u')) / 128;
		checkPos.y = (player.position.y + 10 - 450 + (direction == 'r')) / 128;
	}

	if (dimension == 0) {
		if (not blocks[checkPos.x][checkPos.y].isWalkable) {
			return false;
		}
	}
	else if (dimension == 1) {
		if (not bossBlocks[checkPos.x][checkPos.y].isWalkable) {
			return false;
		}
	}

	return true;
}

void pickUpItem(FloorItem item) {
	for (int i = 0; i < 10; i++) {
		if (hotbar[i].type == item.type) {
			if (hotbar[i].maxStack >= item.stack + hotbar[i].stack) {
				hotbar[i].stack += item.stack;
				return;
			}
			else {
				item.stack -= hotbar[i].maxStack - hotbar[i].stack;
				hotbar[i].stack = hotbar[i].maxStack;
			}

		}
	}
	for (int i = 0; i < 50; i++) {
		if (inventory[i].type == item.type) {
			if (inventory[i].maxStack >= item.stack + inventory[i].stack) {
				inventory[i].stack += item.stack;
				return;
			}
			else {
				item.stack -= inventory[i].maxStack - inventory[i].stack;
				inventory[i].stack = inventory[i].maxStack;
			}

		}
	}
	for (int i = 0; i < 10; i++) {
		if (hotbar[i].type == -1) {
			hotbar[i] = InventoryItem(item.type, item.stack);
			return;
		}
	}
	for (int i = 0; i < 50; i++) {
		if (inventory[i].type == -1) {
			inventory[i] = InventoryItem(item.type, item.stack);
			return;
		}
	}
}

InventoryItem checkCrafts(){
	int itemCount = 0;
	InventoryItem finalItem = InventoryItem(-1, 0);

	vector<int> gridItemTypes;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (craftingGrid[i][j].type != -1) {
				gridItemTypes.push_back(craftingGrid[i][j].type);
				itemCount++;
			}
		}
		
	}
	switch (itemCount) {
	case 0:
		break;
	case 1:
		if (gridItemTypes.at(0) == 6) {
			finalItem = InventoryItem(9, 2);
		}
		break;

	case 2:
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				if (craftingGrid[i][j].type == 9 and craftingGrid[i][j + 1].type == 9) {
					finalItem = InventoryItem(10, 4);
				}
			}
		}
		break;
	case 3:
		for (int i = 0; i < 3; i++) {
			if (craftingGrid[i][0].type == 1 and craftingGrid[i][1].type == 10 and craftingGrid[i][2].type == 10) {
				finalItem = InventoryItem(4, 1);
			}
		}
		break;
	case 4:
		for (int i = 0; i < 2; i++) {
			if (craftingGrid[0][i].type == 1 and craftingGrid[0][i + 1].type == 1 and craftingGrid[2][i].type == 1 and craftingGrid[2][i + 1].type == 1) {
				finalItem = InventoryItem(7, 1);
			}
			else if (craftingGrid[0][i].type == 9 and craftingGrid[1][i].type == 9 and craftingGrid[0][i+1].type == 9 and craftingGrid[1][i + 1].type == 9) {
				finalItem = InventoryItem(11, 1);
			}
		}
		break;
	case 5:
		if (craftingGrid[0][0].type == 9 and craftingGrid[1][0].type == 9 and craftingGrid[2][0].type == 9 and craftingGrid[1][1].type == 10 and craftingGrid[1][2].type == 10) {
			finalItem = InventoryItem(0, 1);
		}
		else if (craftingGrid[0][0].type == 1 and craftingGrid[1][0].type == 1 and craftingGrid[2][0].type == 1 and craftingGrid[1][1].type == 10 and craftingGrid[1][2].type == 10) {
			finalItem = InventoryItem(3, 1);
		}
		else {
			for (int i = 0; i < 2; i++) {
				if (craftingGrid[0][i].type == 1 and craftingGrid[0][i + 1].type == 1 and craftingGrid[1][i].type == 1 and craftingGrid[2][i].type == 1 and craftingGrid[2][i + 1].type == 1) {
					finalItem = InventoryItem(2, 1);
				}
			}
		}
		break;
	case 6:
		break;
	case 7:
		for (int i = 0; i < 7; i++) {
			if (gridItemTypes.at(i) != 1) {
				break;
			}
		}
		if (craftingGrid[1][1].type == -1 and craftingGrid[1][2].type == -1){
			finalItem = InventoryItem(8, 1);
		}
		break;
	case 8:
		for (int i = 0; i < 8; i++) {
			if (gridItemTypes.at(i) != 1) {
				break;
			}
		}
		if (craftingGrid[1][0].type != 1) {
			finalItem = InventoryItem(5, 1);
		}
		break;
	}
	return finalItem;
}

void movePlayer() {
	player.gridPosition.x = floor((player.position.x - 800 + 80) / 128);
	player.gridPosition.y = floor((player.position.y - 450 + 80) / 128);
	float speedMult;
	if (dimension == 0)
	{
		speedMult = blocks[(int)ceil(player.gridPosition.x)][(int)ceil(player.gridPosition.y)].speedMult;
	}
	else if (dimension == 1) {
		speedMult = bossBlocks[(int)ceil(player.gridPosition.x)][(int)ceil(player.gridPosition.y)].speedMult;
	}


	player.isWalking = false;
	if (player.movingUp and checkValidPos('u')) {
		player.move('u', speedMult);
		player.isWalking = true;
	}
	else {
		player.move('d', speedMult);
	}
	if (player.movingDown and checkValidPos('d')) {
		player.move('d', speedMult);
		player.isWalking = true;
	}
	else {
		player.move('u', speedMult);
	}
	if (player.movingLeft and checkValidPos('l')) {
		player.move('l', speedMult);
		player.isWalking = true;
	}
	else {
		player.move('r', speedMult);
	}
	if (player.movingRight and checkValidPos('r')) {
		player.move('r', speedMult);
		player.isWalking = true;
	}
	else {
		player.move('l', speedMult);
	}
}

void drawBlocks() {
	
	int updateCount = 0;
	if (blockSelected.x >= 0 and blockSelected.y >= 0 and blockSelected.x < worldSize and blockSelected.y < worldSize and not blocks[blockSelected.x][blockSelected.y].isWalkable) {
		breakingSprite.setPosition(blocks[blockSelected.x][blockSelected.y].screenPosition.x, blocks[blockSelected.x][blockSelected.y].screenPosition.y);
	}
	else
	{
		breakingSprite.setPosition(-1000, -1000);
	}

	for (int i = player.gridPosition.x-7; i < player.gridPosition.x + 8; i++) {
		for (int j = player.gridPosition.y - 4; j < player.gridPosition.y + 5; j++) {
			if (i >= 0 and i < worldSize and j >= 0 and j < worldSize) {
				if (dimension == 0) {
					if (i >= 0 and i < worldSize and j >= 0 and j < worldSize) {
						updateCount++;
						blocks[i][j].screenPosition.x = i * 128 - player.position.x + 1600;
						blocks[i][j].screenPosition.y = j * 128 - player.position.y + 900;
						blockSprite[i][j].setPosition(blocks[i][j].screenPosition.x, blocks[i][j].screenPosition.y);
						window.draw(blockSprite[i][j]);

						if (blocks[i][j].breakingForce > 0 and blocks[i][j].isBreakable) {
							breakingSprite.setTextureRect(breakingRect[blocks[i][j].getBreakingAnimation()]);
							breakingSprite.setPosition(blocks[blockSelected.x][blockSelected.y].screenPosition.x, blocks[blockSelected.x][blockSelected.y].screenPosition.y);
						}
					}
				}
				else if (dimension == 1) {
					if (i == 0 and j == 0) {
						updateCount++;
						Sprite s;
						s.setTexture(blockTexture);
						s.setTextureRect(blockRect[bossEdge]);
						s.setOrigin(16, 16);
						s.setScale(4, 4);
						s.setPosition(-player.position.x + 1600, -player.position.y + 900);

						window.draw(s);

					}
					else if (i >= 0 and i < 20 and j >= 0 and j < 20) {
						updateCount++;
						bossBlocks[i][j].screenPosition.x = i * 128 - player.position.x + 1600;
						bossBlocks[i][j].screenPosition.y = j * 128 - player.position.y + 900;

						bossBlockSprite[i][j].setPosition(bossBlocks[i][j].screenPosition.x, bossBlocks[i][j].screenPosition.y);
						
						window.draw(bossBlockSprite[i][j]);

						
					}
				}
			}
		}
	}
	
}

void checkPlayerDamage() {
	for (Entity e : entities) {
		int entityX = e.position.x - player.position.x + 1600;
		int entityY = e.position.y - player.position.y + 900;
		int damage;
		if (abs(entityX-800) < 10 + e.size.x and abs(entityY - 450) < 20 + e.size.y) {
			damage = e.damage;
			for (int i = 0; i < 4; i++) {
				damage -= armor[i].damageReduction;
			}
			health -= damage;
			
		}
	}
	if (dimension == 0) {
		switch (blocks[(int)player.gridPosition.x][(int)player.gridPosition.y].type) {
		case 4://hole

			dimension = 1;
			player.position.x = 1000;
			player.position.y = 1000;

			break;
		case 7://lava
			health -= 1;
			break;
		}
	}
	else if (dimension == 1) {
		switch (bossBlocks[(int)player.gridPosition.x][(int)player.gridPosition.y].type) {
		case 4://hole

			dimension = 0;
			player.position.x = 1920;
			player.position.y = 1872;

			break;
		case 7://lava
			health -= 1;
			break;
		}
	}
}

void tick() {
	tickCount++;
	if (tickCount % 40 == 0) {
		if (health < 10) {
			health = min(10.0f, health + 0.25f);
		}
		
	}

	if (tickCount % 10 == 0) {
		checkPlayerDamage();
	}

	if (tickCount % 4 == 0) {
		if (imgCount < 1) {
			imgCount++;
		}
		else {
			imgCount = 0;
		}
		float breakingPower = 1.0f;

		if (blockSelected.x >= 0 and blockSelected.x < worldSize and blockSelected.y > 0 and blockSelected.y < worldSize and dimension == 0) {
			if (blocks[blockSelected.x][blockSelected.y].bestTool == itemHeld.toolType) {
				breakingPower *= itemHeld.toolMult;
			}

			blocks[blockSelected.x][blockSelected.y].breakingForce+=breakingPower;
			if (blocks[blockSelected.x][blockSelected.y].breakingForce > blocks[blockSelected.x][blockSelected.y].toughness and blocks[blockSelected.x][blockSelected.y].isBreakable) {
				floorItems.push_back(FloorItem(blocks[blockSelected.x][blockSelected.y].itemType, 1, blocks[blockSelected.x][blockSelected.y].screenPosition.x + player.position.x - 800, blocks[blockSelected.x][blockSelected.y].screenPosition.y +player.position.y-450));

				breakingSprite.setTextureRect(breakingRect[0]);
				blockSprite[blockSelected.x][blockSelected.y].setTextureRect(blockRect[0]);
				blocks[blockSelected.x][blockSelected.y] = Block(blockSelected.x, blockSelected.y, 0);
				blocks[blockSelected.x][blockSelected.y].breakingForce = 0;
				blocks[blockSelected.x][blockSelected.y].speedMult = 1;
			}
		}
	}
	
}

void drawPlayer(int imgCount) {
	int rectNum;

	switch (player.direction) {
	case 'u':
		if (player.isWalking) {
			if (imgCount == 0) {
				rectNum = 4;
			}
			else
			{
				rectNum = 5;
			}
		}
		else
		{
			rectNum = 3;
		}
		break;
	case 'l':
		if (player.isWalking) {
			if (imgCount == 0) {
				rectNum = 10;
			}
			else
			{
				rectNum = 11;
			}
		}
		else
		{
			rectNum = 9;
		}
		break;
	case 'd':
		if (player.isWalking) {
			if (imgCount == 0) {
				rectNum = 1;
			}
			else
			{
				rectNum = 2;
			}
		}
		else
		{
			rectNum = 0;
		}
		break;
	case 'r':
		if (player.isWalking) {
			if (imgCount == 0) {
				rectNum = 7;
			}
			else
			{
				rectNum = 8;
			}
		}
		else
		{
			rectNum = 6;
		}
		break;

	}
	//rectNum = 2;
	playerSprite.setTextureRect(playerRect[rectNum]);
	window.draw(playerSprite);
}

void drawInventory() {
	window.draw(hotBarSprite);

	if (not inventoryShown) {
		selectedSprite.setPosition(hotbarSlotPos[slotSelected], 840);
		window.draw(selectedSprite);
	}

	for (int i = 0; i < 10; i++) {
		if (hotbar[i].type != -1) {
			Sprite s;
			s.setTexture(itemTexture);
			s.setTextureRect(itemRect[hotbar[i].type]);
			s.setOrigin(16, 16);
			s.setScale(2, 2);
			s.setPosition(hotbarSlotPos[i],840);
			window.draw(s);

			if (hotbar[i].stack > 1)
			{
				Text t;
				t.setFont(font);
				t.setString(to_string(hotbar[i].stack));
				t.setCharacterSize(25);
				t.setFillColor(Color::White);
				t.setPosition(hotbarSlotPos[i] + 10, 850);
				window.draw(t);
			}
			
		}
	}
	if (inventoryShown) {
		
		mousePos = sf::Mouse::getPosition(window);
		slotHover = -1;
		
		
		window.draw(inventorySprite);
		window.draw(armorSprite);
		
		for (int i = 0; i < 50; i++) {
			if (inventory[i].type != -1) {
				Sprite s;
				s.setTexture(itemTexture);
				s.setTextureRect(itemRect[inventory[i].type]);
				s.setOrigin(16, 16);
				s.setScale(2, 2);
				s.setPosition(inventorySlotPos[i]);
				window.draw(s);

				if (inventory[i].stack > 1)
				{
					Text t;
					t.setFont(font);
					t.setString(to_string(inventory[i].stack));
					t.setCharacterSize(25);
					t.setFillColor(Color::White);
					t.setPosition(inventorySlotPos[i].x + 10, inventorySlotPos[i].y + 10);
					window.draw(t);
				}
				
			}
		}

		for (int i = 0; i < 4; i++) {
			if (armor[i].type != -1) {
				Sprite armorSlotSprite;
				armorSlotSprite.setTexture(itemTexture);
				armorSlotSprite.setTextureRect(itemRect[armor[i].type]);
				armorSlotSprite.setOrigin(16, 16);
				armorSlotSprite.setScale(2, 2);
				armorSlotSprite.setPosition(armorSlotPos[i].x, armorSlotPos[i].y);

				if (armor[i].type != -1) {
					window.draw(armorSlotSprite);
				}
			}
		}



		if (not isBigCraft) {
			window.draw(smallCraftSprite);
			for (int i = 0; i < 4; i++) {
				if (craftingGrid[i % 2][(int)i / 2].type != -1) {
					Sprite craftSprite;
					craftSprite.setTexture(itemTexture);
					craftSprite.setTextureRect(itemRect[craftingGrid[i % 2][(int)i / 2].type]);
					craftSprite.setOrigin(16, 16);
					craftSprite.setScale(2, 2);
					craftSprite.setPosition(smallCraftPos[i].x, smallCraftPos[i].y);

					window.draw(craftSprite);
					if (craftingGrid[i % 2][(int)i / 2].stack > 1)
					{
						Text t;
						t.setFont(font);
						t.setString(to_string(craftingGrid[i % 2][(int)i / 2].stack));
						t.setCharacterSize(25);
						t.setFillColor(Color::White);
						t.setPosition(smallCraftPos[i].x + 10, smallCraftPos[i].y + 10);
						window.draw(t);
					}
				}
			}
			craftedItem = checkCrafts();
			if (craftedItem.type != -1) {
				Sprite craftedSprite;
				craftedSprite.setTexture(itemTexture);
				craftedSprite.setTextureRect(itemRect[craftedItem.type]);
				
				craftedSprite.setOrigin(16, 16);
				craftedSprite.setScale(2, 2);
				craftedSprite.setPosition(smallCraftResultPos.x,smallCraftResultPos.y);

				window.draw(craftedSprite);
			}
		}
		else {
			window.draw(bigCraftSprite);
			for (int i = 0; i < 9; i++) {
				if (craftingGrid[i % 3][(int)i / 3].type != -1) {
					Sprite craftSprite;
					craftSprite.setTexture(itemTexture);
					craftSprite.setTextureRect(itemRect[craftingGrid[i % 3][(int)i / 3].type]);
					craftSprite.setOrigin(16, 16);
					craftSprite.setScale(2, 2);
					craftSprite.setPosition(bigCraftPos[i].x, bigCraftPos[i].y);

					window.draw(craftSprite);
					if (craftingGrid[i % 3][(int)i / 3].stack > 1)
					{
						Text t;
						t.setFont(font);
						t.setString(to_string(craftingGrid[i % 3][(int)i / 3].stack));
						t.setCharacterSize(25);
						t.setFillColor(Color::White);
						t.setPosition(bigCraftPos[i].x + 10, bigCraftPos[i].y + 10);
						window.draw(t);
					}
				}
			}
			craftedItem = checkCrafts();
			if (craftedItem.type != -1) {
				Sprite craftedSprite;
				craftedSprite.setTexture(itemTexture);
				craftedSprite.setTextureRect(itemRect[craftedItem.type]);

				craftedSprite.setOrigin(16, 16);
				craftedSprite.setScale(2, 2);
				craftedSprite.setPosition(bigCraftResultPos.x, bigCraftResultPos.y);

				window.draw(craftedSprite);
			}
		}
		Sprite s;
		s.setTexture(itemTexture);
		s.setTextureRect(itemRect[cursorItem.type]);
		s.setOrigin(16, 16);
		s.setScale(2, 2);
		s.setPosition(mousePos.x,mousePos.y);
		if (cursorItem.type != -1) {
			window.draw(s);
		}
		

		if (cursorItem.stack > 1)
		{
			Text t;
			t.setFont(font);
			t.setString(to_string(cursorItem.stack));
			t.setCharacterSize(25);
			t.setFillColor(Color::White);
			t.setPosition(mousePos.x + 10, mousePos.y + 10);
			window.draw(t);
		}
		InventoryItem itemHovered;

		if (mousePos.x >= 320 and mousePos.x <= 1280) {
			if (mousePos.y > 260 and mousePos.y < 740) {
				slotHover = floor((mousePos.y - 260) / 96) * 10 + floor((mousePos.x - 320) / 96);
				itemHovered = inventory[slotHover];
				selectedSprite.setPosition(inventorySlotPos[slotHover]);
				window.draw(selectedSprite);
			}
			if (mousePos.y > 792 and mousePos.y < 886) {
				slotHover = 50 + floor((mousePos.x - 320) / 96);
				selectedSprite.setPosition(hotbarSlotPos[slotHover-50],840);
				window.draw(selectedSprite);
				itemHovered = hotbar[slotHover - 50];
			}
			
		}
		if (mousePos.x > 192 and mousePos.x < 288 and mousePos.y > 308 and mousePos.y < 692) {
			slotHover = 60 + floor((mousePos.y - 308) / 96);
			itemHovered = armor[slotHover - 60];
			selectedSprite.setPosition(armorSlotPos[slotHover - 60].x, armorSlotPos[slotHover - 60].y);
			window.draw(selectedSprite);
		}
		if (not isBigCraft) {
			if (mousePos.x > 58 and mousePos.x < 250 and mousePos.y > 54 and mousePos.y < 246) {
				slotHover = 64 + floor((mousePos.y - 54) / 96) * 2 + floor((mousePos.x - 58) / 96);
				selectedSprite.setPosition(smallCraftPos[slotHover - 64].x, smallCraftPos[slotHover - 64].y);
				window.draw(selectedSprite);
			}
			if (mousePos.x > 346 and mousePos.x < 442 and mousePos.y > 102 and mousePos.y < 198) {
				slotHover = 73;
				itemHovered = craftedItem;
				selectedSprite.setPosition(smallCraftResultPos.x, smallCraftResultPos.y);
				window.draw(selectedSprite);
			}
		}
		else {
			if (mousePos.x > 10 and mousePos.x < 298 and mousePos.y > 6 and mousePos.y < 294) {
				slotHover = 64 + floor((mousePos.y - 6) / 96) * 3 + floor((mousePos.x - 10) / 96);
				selectedSprite.setPosition(bigCraftPos[slotHover - 64].x, bigCraftPos[slotHover - 64].y);
				window.draw(selectedSprite);
			}
			if (mousePos.x > 394 and mousePos.x < 490 and mousePos.y > 102 and mousePos.y < 198) {
				slotHover = 73;
				itemHovered = craftedItem;
				selectedSprite.setPosition(bigCraftResultPos.x, bigCraftResultPos.y);
				window.draw(selectedSprite);
			}
		}
		if (slotHover != -1) {
			itemNameText.setPosition(mousePos.x - 50, mousePos.y);
			itemNameText.setString(itemHovered.name);
			window.draw(itemTextBox);
			window.draw(itemNameText);
		}
	}
}

void updateFloorItems() {
	vector<FloorItem> newItems;
	for (FloorItem item : floorItems) {
		if (abs(item.position.x - player.position.x) < 66 and abs(item.position.y - player.position.y) < 100) {
			pickUpItem(item);
		}
		else
		{
			newItems.push_back(item);
		}
	}
	floorItems = newItems;


	for (FloorItem item: floorItems) {
		Sprite s;
		s.setTexture(itemTexture);
		s.setTextureRect(itemRect[item.type]);
		s.setOrigin(16, 16);
		s.setScale(2, 2);
		s.setPosition(item.position.x - player.position.x + 800, item.position.y - player.position.y + 450);
		window.draw(s);

	}
}

void drawHearts() {
	for (int i = 0; i < 10; i++) {
		Sprite s;
		s.setTexture(heartTexture);
		//health = 6.25;
		if (health - i <= 0) {
			s.setTextureRect(heartRect[4]);
		}
		else if (health - i > 0 and health - i <= 0.25) {
			s.setTextureRect(heartRect[3]);
		}
		else if (health - i > 0.25 and health - i <= 0.5) {
			s.setTextureRect(heartRect[2]);

		}
		else if (health - i > 0.5 and health - i <= 0.75) {
			s.setTextureRect(heartRect[1]);
		}
		else if (health - i > 0.75) {
			s.setTextureRect(heartRect[0]);
		}

		
		s.setOrigin(8, 8);
		s.setScale(2, 2);
		s.setPosition(i * 32 + 340, 770);
		window.draw(s);

		if (health <= 0) {
			state = DEAD;
		}
	}
}

void drawEntities(int imgCount) {
	vector<Entity> newEntities;
	for (Entity e: entities){
		switch (e.type) {
		case 0:
			if (e.dimension == dimension) {
				int bossX = e.position.x - player.position.x + 1600;
				int bossY = e.position.y - player.position.y + 900;

				bossSprite.setPosition(bossX, bossY);
				window.draw(bossSprite);
				int rectNum;

				switch (e.direction) {
				case 'u':
					if (e.isMoving) {
						if (imgCount == 0) {
							rectNum = 4;
						}
						else
						{
							rectNum = 5;
						}
					}
					else
					{
						rectNum = 3;
					}
					break;
				case 'l':
					if (e.isMoving) {
						if (imgCount == 0) {
							rectNum = 10;
						}
						else
						{
							rectNum = 11;
						}
					}
					else
					{
						rectNum = 9;
					}
					break;
				case 'd':
					if (e.isMoving) {
						if (imgCount == 0) {
							rectNum = 1;
						}
						else
						{
							rectNum = 2;
						}
					}
					else
					{
						rectNum = 0;
					}
					break;
				case 'r':
					if (e.isMoving) {
						if (imgCount == 0) {
							rectNum = 7;
						}
						else
						{
							rectNum = 8;
						}
					}
					else
					{
						rectNum = 6;
					}
					break;

				}
				//rectNum = 2;
				bossSprite.setTextureRect(bossRect[rectNum]);
				window.draw(bossSprite);
 			}


		}

		if (e.health > 0) {
			newEntities.push_back(e);
		}
	}
	entities = newEntities;
}

void moveEntities() {
	for (int i = 0; i < entities.size(); i++) {
		switch (entities.at(i).AIType) {
		case 0:
			if (dimension == 1) {
				if (entities.at(i).position.x > player.position.x - 805) {
					entities.at(i).move('l');
				}
				else if (entities.at(i).position.x < player.position.x - 795) {
					entities.at(i).move('r');
				}

				if (entities.at(i).position.y > player.position.y - 445) {
					entities.at(i).move('u');
				}
				else if (entities.at(i).position.y < player.position.y - 455) {
					entities.at(i).move('d');
				}
				
			}
			break;
		}
	}
}

void drawStartScreen() {
	window.draw(homeScreenSprite);
	window.draw(playButton);
	window.draw(playText);
	window.draw(titleText);
}

void drawDeathScreen() {
	Text died;
	died.setFont(font);
	died.setString("YOU DIED");
	died.setCharacterSize(100);
	died.setFillColor(Color::Red);
	died.setPosition(585, 100);

	playText.setString("Respawn");
	playText.setPosition(610, 780);

	Vector2f playBoxBounds;
	playBoxBounds.x = 520;
	playBoxBounds.y = 150;

	playButton.setSize(playBoxBounds);
	playButton.setPosition(710,800);

	window.draw(playButton);
	window.draw(playText);
	window.draw(died);


}
int main()
{
	entities.push_back(Entity(1000, 1000, 0));

	loadAssets();

	player.position.x = 2600;
	player.position.y = 1000;
	float timer = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed and state == ALIVE) {
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					player.movingUp = true;
					player.direction = 'u';
					break;
				case sf::Keyboard::A:
					player.movingLeft = true;
					player.direction = 'l';
					break;
				case sf::Keyboard::S:
					player.movingDown = true;
					player.direction = 'd';
					break;
				case sf::Keyboard::D:
					player.movingRight = true;
					player.direction = 'r';
					break;
				case sf::Keyboard::E:
					inventoryShown = not inventoryShown;
					isBigCraft = false;
					break;

				case sf::Keyboard::Num0:
					slotSelected = 9;
					break;
				case sf::Keyboard::Num1:
					slotSelected = 0;
					break;
				case sf::Keyboard::Num2:
					slotSelected = 1;
					break;
				case sf::Keyboard::Num3:
					slotSelected = 2;
					break;
				case sf::Keyboard::Num4:
					slotSelected = 3;
					break;
				case sf::Keyboard::Num5:
					slotSelected = 4;
					break;
				case sf::Keyboard::Num6:
					slotSelected = 5;
					break;
				case sf::Keyboard::Num7:
					slotSelected = 6;
					break;
				case sf::Keyboard::Num8:
					slotSelected = 7;
					break;
				case sf::Keyboard::Num9:
					slotSelected = 8;
					break;
				default:
					break;
				}
				itemHeld = hotbar[slotSelected];
			}
			if (event.type == sf::Event::KeyReleased and state == ALIVE) {
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					player.movingUp = false;
					break;
				case sf::Keyboard::A:
					player.movingLeft = false;
					break;
				case sf::Keyboard::S:
					player.movingDown = false;
					break;
				case sf::Keyboard::D:
					player.movingRight = false;
					break;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {

				mousePos = sf::Mouse::getPosition(window);

				realMousePos.x = mousePos.x - 736 + player.position.x - 800;
				realMousePos.y = mousePos.y - 386 + player.position.y - 450;

				if (dimension == 0) {
					blockSelected.x = realMousePos.x / 128;
					blockSelected.y = realMousePos.y / 128;
				}

				InventoryItem placeHolderItem = cursorItem;

				switch (event.mouseButton.button) {

				case sf::Mouse::Button::Left:
					if (state == ALIVE) {
						if (inventoryShown) {
							placeHolderItem = cursorItem;

							if (slotHover > -1 and slotHover <= 49) {
								if (cursorItem.type != inventory[slotHover].type) {
									cursorItem = inventory[slotHover];
									inventory[slotHover] = placeHolderItem;
								}
								else if (cursorItem.type == inventory[slotHover].type) {
									if (cursorItem.stack > inventory[slotHover].maxStack - inventory[slotHover].stack) {
										cursorItem.stack = inventory[slotHover].maxStack - inventory[slotHover].stack;
										inventory[slotHover].stack = inventory[slotHover].maxStack;
									}
									else {
										inventory[slotHover].stack += cursorItem.stack;
										cursorItem = InventoryItem(-1, 0);
									}
								}

							}
							else if (slotHover >= 50 and slotHover < 60)
							{
								if (cursorItem.type != hotbar[slotHover - 50].type) {
									cursorItem = hotbar[slotHover-50];
									hotbar[slotHover-50] = placeHolderItem;
								}
								else if (cursorItem.type == hotbar[slotHover-50].type) {
									if (cursorItem.stack > hotbar[slotHover-50].maxStack - hotbar[slotHover-50].stack) {
										cursorItem.stack = hotbar[slotHover-50].maxStack - hotbar[slotHover-50].stack;
										hotbar[slotHover-50].stack = hotbar[slotHover-50].maxStack;
									}
									else {
										hotbar[slotHover-50].stack += cursorItem.stack;
										cursorItem = InventoryItem(-1, 0);
									}
								}

							}
							else if(slotHover >= 60 and slotHover < 64){
								if (((slotHover == 60 and cursorItem.armorType == 'h') or (slotHover == 61 and cursorItem.armorType == 'c') or (slotHover == 62 and cursorItem.armorType == 'p') or(slotHover == 63 and cursorItem.armorType == 'b'))
									or cursorItem.type == -1
									or (armor[slotHover-60].armorType == cursorItem.armorType and cursorItem.armorType != 'n')) {
									cursorItem = armor[slotHover - 60];
									armor[slotHover - 60] = placeHolderItem;
								}
							}
							else if (slotHover >= 64 and slotHover < 68 and not isBigCraft) {
								if (cursorItem.type != craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].type) {
									cursorItem = craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2];
									craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2] = placeHolderItem;
								}
								else if (cursorItem.type == craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].type) {
									if (cursorItem.stack > craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].maxStack - craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack) {
										cursorItem.stack = craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].maxStack - craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack;
										craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack = craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].maxStack;
									}
									else {
										craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack += cursorItem.stack;
										cursorItem = InventoryItem(-1, 0);
									}
								}
								
							}
							else if (slotHover >= 64 and slotHover < 73 and isBigCraft) {
								if (cursorItem.type != craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].type) {
									cursorItem = craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3];
									craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3] = placeHolderItem;
								}
								else if (cursorItem.type == craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].type) {
									if (cursorItem.stack > craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].maxStack - craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack) {
										cursorItem.stack = craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].maxStack - craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack;
										craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack = craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].maxStack;
									}
									else {
										craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack += cursorItem.stack;
										cursorItem = InventoryItem(-1, 0);
									}
								}
							}
							else if (slotHover == 73) {
								if (cursorItem.type == -1 or cursorItem.type == craftedItem.type)
								{
									cursorItem = InventoryItem(craftedItem.type, cursorItem.stack + craftedItem.stack);
									if (cursorItem.type != -1) {
										for (int i = 0; i < 3; i++) {
											for (int j = 0; j < 3; j++) {
												if (craftingGrid[i][j].type != -1) {
													craftingGrid[i][j].stack--;
													if (craftingGrid[i][j].stack == 0) {
														craftingGrid[i][j] = InventoryItem(-1, 0);
													}
												}
											}
										}
									}
								}
							}
						}
						else {
							for (int i = 0; i < entities.size(); i++) {
								vector<Entity> newEntities;
								Entity e = entities.at(i);

								if (abs(realMousePos.x - e.position.x - 60) < e.size.x and abs(realMousePos.y - e.position.y - 65) < e.size.y) {
									e.takeDamage(1+itemHeld.damage);

									realMousePos.x = -10000;
									realMousePos.y = -10000;
								}
								newEntities.push_back(e);
								entities = newEntities;
							}
						}
						leftMouseClicked = true;
					}
					else if (state == START) {
						if (mousePos.x > 650 and mousePos.x < 950 and mousePos.y < 875 and mousePos.y > 725) {
							state = ALIVE;
						}
					}
					else if (state == DEAD) {
						if (mousePos.x > 580 and mousePos.x < 1080 and mousePos.y < 875 and mousePos.y > 725) {
							cout << "Respawning" << endl;
							dimension = 0;
							health = 10.0f;
							state = ALIVE;
							for (int i = 0; i < 50; i++) {
								inventory[i] = InventoryItem(-1, 0);
							}
							for (int i = 0; i < 10; i++) {
								hotbar[i] = InventoryItem(-1, 0);
							}
							for (int i = 0; i < 4; i++) {
								armor[i] = InventoryItem(-1, 0);
							}
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 3; j++) {
									craftingGrid[i][j] = InventoryItem(-1, 0);
								}
							}
							player = Player(8000,2000);
							playerSprite.setPosition(800, 450);
						}
					}

					break;
				case sf::Mouse::Button::Right:
					if (state == ALIVE) {
						rightMouseClicked = true;
						if (not inventoryShown) {
							if (blocks[blockSelected.x][blockSelected.y].type == 8) {
								inventoryShown = true;
								isBigCraft = true;
							}
							else if (itemHeld.blockType != -1 and blocks[blockSelected.x][blockSelected.y].replaceable and not (blockSelected.x == player.gridPosition.x and blockSelected.y == player.gridPosition.y)) {
								blocks[blockSelected.x][blockSelected.y] = Block(blockSelected.x, blockSelected.y, itemHeld.blockType);
								blockSprite[blockSelected.x][blockSelected.y].setTextureRect(blockRect[itemHeld.blockType]);
								hotbar[slotSelected].stack--;
								if (hotbar[slotSelected].stack == 0) {
									hotbar[slotSelected] = InventoryItem(-1, 0);
								}
								itemHeld = hotbar[slotSelected];

							}
							break;
						}
						else {
							if (slotHover > -1 and slotHover <= 49) {
								
								if (cursorItem.type == -1) {
									if (inventory[slotHover].type != -1) {
										cursorItem = InventoryItem(inventory[slotHover].type, ceil((float)inventory[slotHover].stack / 2));
										inventory[slotHover].stack -= cursorItem.stack;
										if (inventory[slotHover].stack <= 0) {
											inventory[slotHover] = InventoryItem(-1, 0);
										}
									}
								}
								else {
									cout << inventory[slotHover].type << " " << cursorItem.type << " " << inventory[slotHover].maxStack << " " << inventory[slotHover].stack << endl;//Doesnt Detect
									if (inventory[slotHover].type == -1) {
										inventory[slotHover] = InventoryItem(cursorItem.type, 1);
										cursorItem.stack--;

										if (cursorItem.stack <= 0) {
											cursorItem = InventoryItem(-1, 0);
										}
									}
									
									else if (inventory[slotHover].type == cursorItem.type and inventory[slotHover].maxStack != inventory[slotHover].stack) {
										
										inventory[slotHover].stack++;
										cursorItem.stack--;

										if (cursorItem.stack <= 0) {
											cursorItem = InventoryItem(-1, 0);
										}
									}
								}
							}
							else if (slotHover >= 50 and slotHover < 60)
							{
								if (cursorItem.type == -1) {
									if (hotbar[slotHover-50].type != -1) {
										cursorItem = InventoryItem(hotbar[slotHover-50].type, ceil((float)hotbar[slotHover-50].stack / 2));
										hotbar[slotHover-50].stack -= cursorItem.stack;
										if (hotbar[slotHover-50].stack <= 0) {
											hotbar[slotHover-50] = InventoryItem(-1, 0);
										}
									}
								}
								else {
									if (hotbar[slotHover-50].type == -1) {
										hotbar[slotHover-50] = InventoryItem(cursorItem.type, 1);
										cursorItem.stack--;

										if (cursorItem.stack <= 0) {
											cursorItem = InventoryItem(-1, 0);
										}
									}

									else if (hotbar[slotHover-50].type == cursorItem.type and hotbar[slotHover-50].maxStack != hotbar[slotHover-50].stack) {

										hotbar[slotHover-50].stack++;
										cursorItem.stack--;

										if (cursorItem.stack <= 0) {
											cursorItem = InventoryItem(-1, 0);
										}
									}
								}

							}
							else if (slotHover >= 60 and slotHover < 64) {
								if (((slotHover == 60 and cursorItem.armorType == 'h') or (slotHover == 61 and cursorItem.armorType == 'c') or (slotHover == 62 and cursorItem.armorType == 'p') or (slotHover == 63 and cursorItem.armorType == 'b'))
									or cursorItem.type == -1
									or (armor[slotHover - 60].armorType == cursorItem.armorType and cursorItem.armorType != 'n')) {
									cursorItem = armor[slotHover - 60];
									armor[slotHover - 60] = placeHolderItem;
								}
							}
							else if (slotHover >= 64 and slotHover < 68 and not isBigCraft) {
								if (cursorItem.type == -1) {
									if (craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].type != -1) {
										cursorItem = InventoryItem(craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].type, ceil((float)craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack / 2));
										craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack -= cursorItem.stack;
										if (craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack <= 0) {
											craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2] = InventoryItem(-1, 0);
										}
									}
								}
								else {
									if (craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].type == -1) {
										craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2] = InventoryItem(cursorItem.type, 1);
										cursorItem.stack--;

										if (cursorItem.stack <= 0) {
											cursorItem = InventoryItem(-1, 0);
										}
									}

									else if (craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].type == cursorItem.type and craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].maxStack != craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack) {

										craftingGrid[(slotHover - 64) % 2][(int)(slotHover - 64) / 2].stack++;
										cursorItem.stack--;

										if (cursorItem.stack <= 0) {
											cursorItem = InventoryItem(-1, 0);
										}
									}
								}
								
							}
							else if (slotHover >= 64 and slotHover < 73 and isBigCraft) {
								if (cursorItem.type == -1) {
									if (craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].type != -1) {
										cursorItem = InventoryItem(craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].type, ceil((float)craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack / 2));
										craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack -= cursorItem.stack;
										if (craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack <= 0) {
											craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3] = InventoryItem(-1, 0);
										}
									}
								}
								else {
									if (craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].type == -1) {
										craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3] = InventoryItem(cursorItem.type, 1);
										cursorItem.stack--;

										if (cursorItem.stack <= 0) {
											cursorItem = InventoryItem(-1, 0);
										}
									}

									else if (craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].type == cursorItem.type and craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].maxStack != craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack) {

										craftingGrid[(slotHover - 64) % 3][(int)(slotHover - 64) / 3].stack++;
										cursorItem.stack--;

										if (cursorItem.stack <= 0) {
											cursorItem = InventoryItem(-1, 0);
										}
									}
								}
							}
							else if (slotHover == 73) {
								if (cursorItem.type == -1 or cursorItem.type == craftedItem.type)
								{
									cursorItem = InventoryItem(craftedItem.type, cursorItem.stack + craftedItem.stack);
									if (craftedItem.type != -1) {
										for (int i = 0; i < 3; i++) {
											for (int j = 0; j < 3; j++) {
												if (craftingGrid[i][j].type != -1) {
													craftingGrid[i][j].stack--;
													if (craftingGrid[i][j].stack == 0) {
														craftingGrid[i][j] = InventoryItem(-1, 0);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}

				
				

			}
			if (event.type == sf::Event::MouseButtonReleased and state == ALIVE) {
				breakingSprite.setTextureRect(breakingRect[0]);
				if (blockSelected.x >= 0 and blockSelected.x < worldSize and blockSelected.y > 0 and blockSelected.y < worldSize) {
					blocks[blockSelected.x][blockSelected.y].breakingForce = 0;
				}
				blockSelected.x = -100000;
				blockSelected.y = -100000;

				switch (event.mouseButton.button) {
				case sf::Mouse::Button::Left:
					leftMouseClicked = false;
				case sf::Mouse::Button::Right:
					rightMouseClicked = false;
				}
			}
		}

		playerSprite.setTextureRect(playerRect[imgCount]);

		timer = c.getElapsedTime().asSeconds();
		if (timer > 0.05f) {
			tick();
			c.restart();
		}

		window.clear();
		if (state == ALIVE) {
			movePlayer();
			moveEntities();
			drawBlocks();
			window.draw(breakingSprite);
			drawHearts();
			updateFloorItems();
			drawEntities(imgCount);
			drawPlayer(imgCount);
			drawInventory();
		}
		else if(state == START){
			window.clear(Color::White);
			drawStartScreen();
		}
		else if(state = DEAD) {
			drawBlocks();
			drawEntities(0);
			drawPlayer(0);
			drawDeathScreen();
		}
		

		window.display();
		
	}
}
