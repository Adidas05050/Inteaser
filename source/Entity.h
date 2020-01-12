#ifndef ENTITY_H
#define ENTITY_H

#include "SFML.hpp"
#include "Tile.h"

class Entity {
	public:
		int getHealth();
		int getSpeed();
		sf::FloatRect getRect();
		float getCenterX();
		float getCenterY();

		std::vector<TmxObject> obj;
	protected:
		int mFrame;
		int mSpeed;
		int mHealth;
		sf::FloatRect mBox;
		sf::Texture texture;

};

#endif
