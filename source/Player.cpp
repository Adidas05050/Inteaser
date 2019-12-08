#include "Player.h"
#include "iostream"
Player::Player(int x, int y, int health, int speed) {
	mBox.left = x;
	mBox.top = y;
	mHealth = health;
	mSpeed = speed;
	mBox.width = 48;
	mBox.height = 24;
	sPlayer.setPosition(getX(), getY());
	sPlayer.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	texture.loadFromFile("media/hero/Player.png");
	sPlayer.setTexture(texture);
	direction = 0;
	frame = 0;
	spriteTile = 0;
}

void Player::draw(sf::RenderWindow* Window, int scaleX, int scaleY) {
	float width = scaleX * mBox.width; 
	float height = scaleY * mBox.height;
	float playerWidth = width / (float) mBox.width;
	float playerHeight = height / (float) mBox.height;
	sPlayer.setTextureRect(sf::IntRect(spriteTile*24, 24*direction, PLAYER_WIDTH, PLAYER_HEIGHT));
	sPlayer.setScale(playerWidth, playerHeight);
	sPlayer.setPosition(mBox.left, mBox.top);
	Window->draw(sPlayer);
}

void Player::move(int direction) {
	if (direction == 2) //left
	{
		mBox.left -= mSpeed; 
		if(frame % 4 == 0)
		{
			frame = 0;
			spriteTile++;
		}
		if(spriteTile > 7)
		{
			spriteTile = 0;
		}
		frame++;
	}
	if (direction == 1) //Right
	{
		mBox.left += mSpeed;
		if(frame % 4 == 0)
		{
			frame = 0;
			spriteTile++;
		}
		if(spriteTile > 7)
		{
			spriteTile = 0;
		}
		frame++;
	}
	if (direction == 3) //Up
		mBox.top -= mSpeed;
	if (direction == 4) //Down
		mBox.top += mSpeed;
}
