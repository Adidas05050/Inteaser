#ifndef TILE_H
#define TILE_H

#include "SFML.hpp"

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = 600;
const int LEVEL_WIDTH = 960;
const int LEVEL_HEIGHT = 640;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WOOD = 0;
const int TILE_STONE = 1;
const int TILE_DESERT = 2;
const int TILE_END = 3;

extern sf::IntRect gTileClips[TILE_END];
extern sf::Texture tBackground;

class Tile  {
	public:
		Tile(int x, int y, int tileType);
	
		void draw(sf::RenderWindow *Window);
		
		int getType();
		sf::IntRect getBox();
		
	private:
		int mType;
		sf::IntRect mBox;
};

bool setTiles( Tile* tiles[], std::string path );

#endif
