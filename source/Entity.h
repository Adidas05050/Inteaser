#ifndef ENTITY_H
#define ENTITY_H

#include "SFML.hpp"

class Entity
{
	public:
		int getX();
		int getY();
		int getHealth();
		int getSpeed();
		int getWidth();
		int getHeight();
		float getCenterX();
		float getCenterY();
		
		
	protected:
		sf::Texture texture;
		sf::IntRect mBox;
		int mHealth;
		int mSpeed;
		
};

#endif
