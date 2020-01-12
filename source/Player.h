#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

const int PLAYER_WIDTH = 24;
const int PLAYER_HEIGHT = 24;

class Player : public Entity {

	public:
		Player(int x, int y, int health, int speed, Tile *level);
		void draw(sf::RenderWindow* Window, int scaleX, int scaleY);
		void move();
		void collision();
		
	private:
		sf::Sprite sPlayer;
		int	mSpriteTile;
		int mDirection;

};

#endif
