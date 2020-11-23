#include "Entity.h"

float Entity::getCenterX() {
	float centerX = (mBox.width / 2) + mBox.left;
	return centerX;
}

float Entity::getCenterY() {
	float centerY = (mBox.height / 2) + mBox.top;
	return centerY;
}

sf::FloatRect Entity::getRect() {
	return mBox;
}

int Entity::getHealth() {
	return mHealth;
}

int Entity::getSpeed() {
	return mSpeed;
}

bool Entity::alive() {
	return (mHealth > 0? true: false);
}

