#include "Player.h"
#include "iostream"
Player::Player(int x, int y, int health, int speed, Tile *level) {
	mBox.left = x;
	mBox.top = y;
	mBox.width = 48;
	mBox.height = 24;

	mHealth = health;
	mSpeed = speed;

	forJump.x = 0;
	forJump.y = 0;

	sPlayer.setPosition(2500, 2000);
	sPlayer.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	texture.loadFromFile("media/hero/Player.png");
	sPlayer.setTexture(texture);
	mFrame = 0;
	mSpriteTile = 0;
	mScale = 1;
	objSolid = level->GetAllObjects("wall");
	mObjectSound = level->GetAllObjects("sound");
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
		sPlayer.setScale(playerWidth * (-1) * mScale, playerHeight * mScale);
		sPlayer.setPosition(mBox.left + PLAYER_WIDTH*3 + forJump.x, mBox.top + forJump.y);
	} else {
		sPlayer.setScale(playerWidth * mScale, playerHeight * mScale);
		sPlayer.setPosition(mBox.left + forJump.x, mBox.top + forJump.y);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		mBox.left += mSpeed;
		isLeftDirection = false;
		isStay = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		mBox.left-= mSpeed;
		isLeftDirection = true;
		isStay = false;
	}

	//*****Jump
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and canJump) {
		canJump = false;
		std::cout <<"1";
	}
	if(!canJump and mScale <= 1.5f and !inAir) {
		mScale += 0.1;
		forJump.x -= 3;
		forJump.y -= 12;
	} else if (mScale > 1.f) {
		mScale -= 0.1;
		forJump.x += 3;
		forJump.y += 12;
		inAir = true;
	} else {
		canJump = true;
		inAir = false;
	}
	//------
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
			if(!stepSound[currentNumberSound].getStatus()) {
				stepSound[currentNumberSound].setPitch(1.5f);
				//stepSound[currentNumberSound].play(); //MUSIC
			}
		}
	}

}

void Player::collisionSound() {
	for(int i = 0; i < mObjectSound.size(); i++) {
		if( getRect().intersects(mObjectSound[i].rect) and (previousNameSound != mObjectSound[i].type)) {
			previousNameSound = mObjectSound[i].type;
			for(it = tileMap.begin(); it != tileMap.end(); it++) {
				if(it->second == previousNameSound) {
					currentNumberSound = it->first;
					break;
				}
			}
			//std::cout << currentNumberSound << " " << previousNameSound;
		}
	}
}

void Player::collision(sf::FloatRect enemyRect) { //ѕока только один потом массив надо сделать TODO

	for(int i = 0; i < objSolid.size(); i++) {

		mBox.top += mSpeed;
		if( getRect().intersects(objSolid[i].rect)) {
			mBox.top -= mSpeed;
		}
		mBox.top -= mSpeed;

		mBox.left += mSpeed;
		if( getRect().intersects(objSolid[i].rect) ) {
			mBox.left -= mSpeed;
		}
		mBox.left -= mSpeed;

		mBox.left -= mSpeed;
		if( getRect().intersects(objSolid[i].rect) ) {
			mBox.left += mSpeed;
		}
		mBox.left += mSpeed;

		mBox.top -= mSpeed;
		if( getRect().intersects(objSolid[i].rect) ) {
			mBox.top += mSpeed;
		}
		mBox.top += mSpeed;
	}
	
	for(int i = 0; i < 1; i++) {

		mBox.top += mSpeed;
		if( getRect().intersects(enemyRect) ) {
			mBox.top -= mSpeed;
		}
		mBox.top -= mSpeed;

		mBox.left += mSpeed;
		if( getRect().intersects(enemyRect) ) {
			mBox.left -= mSpeed;
		}
		mBox.left -= mSpeed;

		mBox.left -= mSpeed;
		if( getRect().intersects(enemyRect) ) {
			mBox.left += mSpeed;
		}
		mBox.left += mSpeed;

		mBox.top -= mSpeed;
		if( getRect().intersects(enemyRect) ) {
			mBox.top += mSpeed;
		}
		mBox.top += mSpeed;
	}
	
}
