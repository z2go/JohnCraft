#include "FloorItem.h"

FloorItem::FloorItem() {

}

FloorItem::FloorItem(int t, int s, int x, int y) {
	type = t;
	stack = s;
	position.x = x;
	position.y = y;
}