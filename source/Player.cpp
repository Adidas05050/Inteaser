#include "Player.h"

Player::Player(int x, int y, int health, int speed) {
	setX(x);
	setY(y);
	setHealth(health);
	setSpeed(speed);
	setHeight(24);
	setWidth(48);
	sPlayer.setPosition(getX(), getY());
	sPlayer.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	texture.loadFromFile("media/hero/Player.png");
	sPlayer.setTexture(texture);
}

void Player::draw(sf::RenderWindow* Window, int scaleX, int scaleY) {
	float width = scaleX * getWidth(); 
	float height = scaleY * getHeight();
	float playerWidth = width / (float) texture.getSize().x;
	float playerHeight = height / (float) texture.getSize().y;
	sPlayer.setScale(playerWidth*2, playerHeight*2);
	Window->draw(sPlayer);
}

void Player::move(int direction) {
	if (direction == 0) //left
	{
		sPlayer.move(-0.1, 0);
		if(frame % 100 == 0)
		{
			sPlayer.setTextureRect(sf::IntRect(spriteTile, 48, PLAYER_WIDTH, PLAYER_HEIGHT));
			spriteTile += 24;
		}
		else if(frame > 800)
		{
			spriteTile = 0;
			frame = 0;
		}
		frame++;
	}

	if (direction == 1) //Right
	{
		sPlayer.move(0.1, 0);
		if(frame % 100 == 0)
		{
			sPlayer.setTextureRect(sf::IntRect(spriteTile, 24, PLAYER_WIDTH, PLAYER_HEIGHT));
			spriteTile += 24;
		}
		else if(frame > 800)
		{
			spriteTile = 0;
			frame = 0;
		}
		frame++;
	}
	if (direction == 2) //Up
		sPlayer.move(0, -0.1);
	if (direction == 3) //Down
		sPlayer.move(0, 0.1);
	if (direction == 4) //Stop
		sPlayer.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
}
