#include "Entity.h"

//-------------//
void Entity::setX(int x) {
	mX = x;
}
void Entity::setY(int y) {
	mY = y;
}
void Entity::setHealth(int health) {
	mHealth = health;
}
void Entity::setSpeed(int speed) {
	mSpeed = speed;
}
void Entity::setWidth(int width) {
	mWidth = width;
}
void Entity::setHeight(int height) {
	mHeight = height;
}
//-------------//
int Entity::getX() {
	return mX;
}
int Entity::getY() {
	return mY;
}
int Entity::getHealth() {
	return mHealth;
}
int Entity::getSpeed() {
	return mSpeed;
}
int Entity::getWidth() {
	return mWidth;
}
int Entity::getHeight() {
	return mHeight;
}
