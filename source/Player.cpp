#include "Player.h"

Player::Player(int x, int y, int health, int speed) {
	setX(x);
	setY(y);
	setHealth(health);
	setSpeed(speed);
	setHeight(24);
	setWidth(24);
	texture.loadFromFile("media/hero/Player.png");
}

void Player::draw(sf::RenderWindow* Window, int scaleX, int scaleY) {
	sf::Sprite sPlayer;
	sPlayer.setTexture(texture);
	sPlayer.setTextureRect(sf::IntRect(0, 0, 24, 24));
//	float width = scaleX * getWidth(); 
//	float height = scaleY * getHeight();
	sPlayer.setPosition(getX(), getY());
//	float playerWidth = width / (float) texture.getSize().x;
//	float playerHeight = height / (float) texture.getSize().y;
//	sPlayer.setScale(playerWidth, playerHeight);
//	sPlayer.setScale(24, 24);
	Window->draw(sPlayer);
}

