#include "skelet.h"

Skelet::Skelet(int health, int speed, Tile *level) {
	mBox.left = -1;
	mBox.top = -1;
	mBox.width = 24;
	mBox.height = 48;

	mHealth = health;
	mSpeed = speed;

	texture.loadFromFile("media/enemy/skelet.png");
	sSkelet.setTexture(texture);
	objSolid = level->GetAllObjects("wall");
	mObjectSound = level->GetAllObjects("sound");
}

void Skelet::spawn(int x, int y, int health) {
	sSkelet.setPosition(x, y);
	mBox.left = x;
	mBox.top = y;
	mHealth = 100;
}

void Skelet::draw(sf::RenderWindow* Window, float scaleX, float scaleY) {
	float width = scaleX * mBox.width;
	float height = scaleY * mBox.height;
	float skeletWidth = width / (float) mBox.width;
	float skeletHeight = height / (float) mBox.height;
	sSkelet.setScale(skeletWidth, skeletHeight);
	if(mBox.left != -1 )
		Window->draw(sSkelet);
}
