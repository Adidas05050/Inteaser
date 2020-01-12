#include "Player.h"
#include "iostream"
Player::Player(int x, int y, int health, int speed, Tile *level) {
	mBox.left = x;
	mBox.top = y;
	mHealth = health;
	mSpeed = speed;
	mBox.width = 48;
	mBox.height = 24;
	sPlayer.setPosition(2500, 2000);
	sPlayer.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	texture.loadFromFile("media/hero/Player.png");
	sPlayer.setTexture(texture);
	mDirection = 0;
	mFrame = 0;
	mSpriteTile = 0;
	obj = level->GetAllObjects("wall");
}

void Player::draw(sf::RenderWindow* Window, int scaleX, int scaleY) {
	float width = scaleX * mBox.width;
	float height = scaleY * mBox.height;
	float playerWidth = width / (float) mBox.width;
	float playerHeight = height / (float) mBox.height;
	if(mDirection == 5)
		sPlayer.setTextureRect(sf::IntRect(mSpriteTile*24, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	else
		sPlayer.setTextureRect(sf::IntRect(mSpriteTile*24, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
	if(mDirection == 2) {
		sPlayer.setScale(playerWidth * (-1), playerHeight);
		sPlayer.setPosition(mBox.left + PLAYER_WIDTH*3, mBox.top);

	} else {
		sPlayer.setScale(playerWidth, playerHeight);
		sPlayer.setPosition(mBox.left, mBox.top);
	}
	Window->draw(sPlayer);
}

void Player::move() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mBox.top -= mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mBox.left-= mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mBox.left += mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mBox.top += mSpeed;
	}
}

void Player::collision() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mBox.top += mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mBox.left += mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mBox.left -= mSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mBox.top -= mSpeed;
	}
}
