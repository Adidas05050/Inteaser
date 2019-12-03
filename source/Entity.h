#ifndef ENTITY_H
#define ENTITY_H

#include "SFML.hpp"

class Entity
{
	public:
		void setX(int x);
		void setY(int y);
		void setHealth(int health);
		void setSpeed(int speed);
		void setWidth(int width);
		void setHeight(int height);
		int getX();
		int getY();
		int getHealth();
		int getSpeed();
		int getWidth();
		int getHeight();

		
		
	protected:
		sf::Texture texture;
		
	private:
		int mWidth;
		int mHeight;
		int mX;
		int mY;
		int mHealth;
		int mSpeed;
};

#endif
