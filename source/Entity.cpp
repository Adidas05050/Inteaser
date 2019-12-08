#include "Entity.h"
float Entity::getCenterX(){
	float centerX = (mBox.width / 2) + mBox.left;
	return centerX;
}
float Entity::getCenterY(){
	float centerY = (mBox.height / 2) + mBox.top;
	return centerY;
}
int Entity::getX() {
	return mBox.left;
}
int Entity::getY() {
	return mBox.top;
}
int Entity::getHealth() {
	return mHealth;
}
int Entity::getSpeed() {
	return mSpeed;
}
int Entity::getWidth() {
	return mBox.width;
}
int Entity::getHeight() {
	return mBox.height;
}
