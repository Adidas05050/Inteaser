#ifndef SKELET_H
#define SKELET_H

#include "Entity.h"
#include "Music.h"

class Skelet : public Entity {
	public:
		Skelet(int health, int speed, Tile *level);
		void spawn(int x, int y, int health);
		void draw(sf::RenderWindow* Window, float scaleX, float scaleY);
		
	protected:
		std::vector<TmxObject> mObjectSound;

		sf::Sprite sSkelet;
		int	mSpriteTile;
};

#endif
