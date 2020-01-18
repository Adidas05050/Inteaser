#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Music.h"


class Player : public Entity, public Music {

	public:
		Player(int x, int y, int health, int speed, Tile *level);
		void draw(sf::RenderWindow* Window, int scaleX, int scaleY);
		void move();
		void collision();
		void collisionSound();

		const int PLAYER_WIDTH = 24;
		const int PLAYER_HEIGHT = 24;
		const int PLAYER_FRAME = 8;

	private:
		std::vector<TmxObject> mObjectSound;
		
		sf::Sprite sPlayer;
		int	mSpriteTile;
		bool isLeftDirection = false;
		bool isStay = true;
};

#endif
