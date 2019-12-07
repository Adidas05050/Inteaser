#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
	public:
		Player(int x, int y, int health, int speed);
		void draw(sf::RenderWindow* Window, int scaleX, int scaleY);
};

#endif
