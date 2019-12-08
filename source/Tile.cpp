#include "Tile.h"


Tile::Tile(int x, int y, int tileType) {
	mBox.left = x;
	mBox.top = y;
	mBox.width = TILE_WIDTH;
	mBox.height = TILE_HEIGHT;
	mType = tileType;
}

void Tile::draw(sf::RenderWindow *Window) {
	
	sf::Sprite sBackground;
	sBackground.setTexture(tBackground);
	sBackground.setTextureRect(gTileClips[mType]);
	sBackground.setPosition(mBox.left, mBox.top);
	float WidgetWidth = (float)mBox.width/(float)TILE_WIDTH;
	float WidgetHeight = (float)mBox.height/(float)TILE_HEIGHT;
	sBackground.setScale(WidgetWidth, WidgetHeight);
	Window->draw(sBackground);
}

int Tile::getType(){
    return mType;
}

sf::IntRect Tile::getBox(){
    return mBox;
}
