#include "Player.h"
#include "iostream"

Player::Player(int x, int y, int health, int speed, Tile *level, sf::RenderWindow* window) {
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

	m_healthBar = new ProgressBar(sf::Vector2f(100, 20), sf::Color::Red);
	m_foodBar = new ProgressBar(sf::Vector2f(100, 20), sf::Color::Yellow);

	m_healthBar->SetProgress(mHealth / m_maxHealth);
	m_foodBar->SetProgress(m_food / m_maxFood);

	m_healthBar->SetPosition(sf::Vector2f(10, 10));
	m_foodBar->SetPosition(sf::Vector2f(10, 35));

	m_window = window;
}
//-------------------------------------------------------
void Player::OnFrame(sf::RenderWindow* Window, sf::View* view)
{
	if(m_food > FLT_MIN)
		m_food -= m_decreaseFood;
	
	if (m_food < m_maxFood / 2 and mHealth > m_maxHealth / 2)
		mHealth -= m_decreaseFood;
	m_healthBar->SetProgress(mHealth/ m_maxHealth);
	m_foodBar->SetProgress(m_food/ m_maxFood);
	m_healthBar->Draw(Window, view);
	m_foodBar->Draw(Window, view);
}
//-------------------------------------------------------
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
//-------------------------------------------------------
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
				stepSound[currentNumberSound].play(); //MUSIC
			}
		}
	}

}
//-------------------------------------------------------
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
//-------------------------------------------------------
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
//-------------------------------------------------------
Player::ProgressBar::ProgressBar(sf::Vector2f size, sf::Color color)
{
	m_background.setSize(size);
	m_background.setFillColor(sf::Color::Black);
	m_foreground.setSize(size);
	m_foreground.setFillColor(color);
}
//-------------------------------------------------------
void Player::ProgressBar::SetProgress(float progress)
{
	m_foreground.setScale(progress, 1.f);
}
//-------------------------------------------------------
void Player::ProgressBar::SetColor(sf::Color color)
{
	m_foreground.setFillColor(color);
}
//-------------------------------------------------------
void Player::ProgressBar::SetPosition(sf::Vector2f position)
{
	m_position = position;
}
//-------------------------------------------------------
void Player::ProgressBar::Draw(sf::RenderWindow* window, sf::View* view)
{
	const auto& coordBegin = view->getCenter() - view->getSize() / 2.f;
	sf::Vector2f positionOnView = sf::Vector2f(m_position.x + coordBegin.x, m_position.y + coordBegin.y);
	m_background.setPosition(positionOnView);
	m_foreground.setPosition(positionOnView);
	window->draw(m_background);
	window->draw(m_foreground);
}
//-------------------------------------------------------