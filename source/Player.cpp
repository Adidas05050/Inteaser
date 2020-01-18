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
	mFrame = 0;
	mSpriteTile = 0;
	obj = level->GetAllObjects("wall");
}

void Player::draw(sf::RenderWindow* Window, int scaleX, int scaleY) {
	float width = scaleX * mBox.width;
	float height = scaleY * mBox.height;
	float playerWidth = width / (float) mBox.width;
	float playerHeight = height / (float) mBox.height;
	if( isStay )
		sPlayer.setTextureRect(sf::IntRect(mSpriteTile*24, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	else
		sPlayer.setTextureRect(sf::IntRect(mSpriteTile*24, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));

	if( isLeftDirection ) {
		sPlayer.setScale(playerWidth * (-1), playerHeight);
		sPlayer.setPosition(mBox.left + PLAYER_WIDTH*3, mBox.top);
	} else {
		sPlayer.setScale(playerWidth, playerHeight);
		sPlayer.setPosition(mBox.left, mBox.top);
	}
	Window->draw(sPlayer);
}

void Player::move() {
	mFrame++;
	if(mFrame > 64) {
		mFrame = 0;
	}
	isStay = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		mBox.top -= mSpeed;
		isStay = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		mBox.top += mSpeed;
		isStay = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mBox.left-= mSpeed;
		isLeftDirection = true;
		isStay = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mBox.left += mSpeed;
		isLeftDirection = false;
		isStay = false;
	}

	if(mSpriteTile > PLAYER_FRAME/2 - 1 and isStay) {
		mSpriteTile = 0;
	}

	if(mFrame % 4 == 0) {
		if( isStay ) {
			if(mSpriteTile < PLAYER_FRAME/2 - 1)
				mSpriteTile++;
			else
				mSpriteTile = 0;
		} else {
			if(mSpriteTile < PLAYER_FRAME - 1)
				mSpriteTile++;
			else
				mSpriteTile = 0;
		}
	}
	std::cout << mSpriteTile << std::endl;
}

void Player::collision() {

	for(int i = 0; i < obj.size(); i++) {

		mBox.top += mSpeed;
		if(getRect().intersects(obj[i].rect)) {
			mBox.top -= mSpeed;
		}
		mBox.top -= mSpeed;

		mBox.left += mSpeed;
		if(getRect().intersects(obj[i].rect)) {
			mBox.left -= mSpeed;
		}
		mBox.left -= mSpeed;

		mBox.left -= mSpeed;
		if(getRect().intersects(obj[i].rect)) {
			mBox.left += mSpeed;
		}
		mBox.left += mSpeed;

		mBox.top -= mSpeed;
		if(getRect().intersects(obj[i].rect)) {
			mBox.top += mSpeed;
		}
		mBox.top += mSpeed;
	}
}
