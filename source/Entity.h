#ifndef ENTITY_H
#define ENTITY_H

#include "SFML.hpp"
#include "Tile.h"

class Entity {
	public:
		int mSpeed = 0;
		int getHealth();
		int getSpeed();
		sf::FloatRect getRect();
		float getCenterX();
		float getCenterY();
		bool alive();
		
		std::vector<TmxObject> objSolid;
	protected:
		int mFrame = 0;
		int mHealth = 0;
		sf::FloatRect mBox;
		sf::Texture texture;

};

#endif
