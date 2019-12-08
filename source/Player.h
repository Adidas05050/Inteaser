#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

const int PLAYER_WIDTH = 24;
const int PLAYER_HEIGHT = 24;

class Player : public Entity
{
	public:
		Player(int x, int y, int health, int speed);
		void draw(sf::RenderWindow* Window, int scaleX, int scaleY);
		void move(int direction);
		int frame;
		int	spriteTile;
		int direction;
	private:
		sf::Sprite sPlayer;		
		
};

#endif
