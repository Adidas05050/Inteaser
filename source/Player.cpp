#include "Player.h"
#include "iostream"

Player::Player(int x, int y, int health, int speed, Tile *level, sf::RenderWindow* window) {
	m_box.left = x;
	m_box.top = y;
	m_box.width = 48;
	m_box.height = 24;

	m_health = health;
	m_speed = speed;

	m_forJump.x = 0;
	m_forJump.y = 0;

	m_playerSprite.setPosition(x, y);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	m_texture.loadFromFile("media/hero/Player.png");
	m_playerSprite.setTexture(m_texture);
	m_frame = 0;
	m_spriteTile = 0;
	m_scale = 1;
	m_objectsSolid = level->GetAllObjects("wall");
	m_objectsSound = level->GetAllObjects("sound");

	m_healthBar = new ProgressBar(sf::Vector2f(100, 20), sf::Color::Red);
	m_foodBar = new ProgressBar(sf::Vector2f(100, 20), sf::Color::Yellow);

	m_healthBar->SetProgress(m_health / m_maxHealth);
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
	
	if (m_food < m_maxFood / 2 and m_health > m_maxHealth / 2)
		m_health -= m_decreaseFood;
	m_healthBar->SetProgress(m_health/ m_maxHealth);
	m_foodBar->SetProgress(m_food/ m_maxFood);
	m_healthBar->Draw(Window, view);
	m_foodBar->Draw(Window, view);
}
//-------------------------------------------------------
void Player::Draw(sf::RenderWindow* Window, int scaleX, int scaleY) {
	float width = scaleX * m_box.width;
	float height = scaleY * m_box.height;
	float playerWidth = width / (float) m_box.width;
	float playerHeight = height / (float) m_box.height;
	if( m_isStay )
		m_playerSprite.setTextureRect(sf::IntRect(m_spriteTile*24, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
	else
		m_playerSprite.setTextureRect(sf::IntRect(m_spriteTile*24, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));

	if( m_isLeftDirection ) {
		m_playerSprite.setScale(playerWidth * (-1) * m_scale, playerHeight * m_scale);
		m_playerSprite.setPosition(m_box.left + PLAYER_WIDTH*3 + m_forJump.x, m_box.top + m_forJump.y);
	} else {
		m_playerSprite.setScale(playerWidth * m_scale, playerHeight * m_scale);
		m_playerSprite.setPosition(m_box.left + m_forJump.x, m_box.top + m_forJump.y);
	}
	Window->draw(m_playerSprite);
}
//-------------------------------------------------------
void Player::Move() {
	m_frame++;
	if(m_frame > 64) {
		m_frame = 0;
	}
	m_isStay = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_box.top -= m_speed;
		m_isStay = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_box.top += m_speed;
		m_isStay = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_box.left += m_speed;
		m_isLeftDirection = false;
		m_isStay = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_box.left-= m_speed;
		m_isLeftDirection = true;
		m_isStay = false;
	}

	//*****Jump
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and m_isCanJump) {
		m_isCanJump = false;
		std::cout <<"1";
	}
	if(!m_isCanJump and m_scale <= 1.5f and !m_isInAir) {
		m_scale += 0.1;
		m_forJump.x -= 3;
		m_forJump.y -= 12;
	} else if (m_scale > 1.f) {
		m_scale -= 0.1;
		m_forJump.x += 3;
		m_forJump.y += 12;
		m_isInAir = true;
	} else {
		m_isCanJump = true;
		m_isInAir = false;
	}
	//------
	if(m_spriteTile > PLAYER_FRAME/2 - 1 and m_isStay) {
		m_spriteTile = 0;
	}

	if(m_frame % 4 == 0) {
		if( m_isStay ) {
			if(m_spriteTile < PLAYER_FRAME/2 - 1)
				m_spriteTile++;
			else
				m_spriteTile = 0;
		} else {
			if(m_spriteTile < PLAYER_FRAME - 1)
				m_spriteTile++;
			else
				m_spriteTile = 0;
			if(!stepSound[currentNumberSound].getStatus()) {
				stepSound[currentNumberSound].setPitch(1.5f);
				//stepSound[currentNumberSound].play(); //MUSIC
			}
		}
	}

}
//-------------------------------------------------------
void Player::CollisionSound() {
	for(int i = 0; i < m_objectsSound.size(); i++) {
		if( GetRect().intersects(m_objectsSound[i].rect) and (previousNameSound != m_objectsSound[i].type)) {
			previousNameSound = m_objectsSound[i].type;
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
void Player::Ñollision(sf::FloatRect enemyRect) 
{
	for(int i = 0; i < m_objectsSolid.size(); i++)
	{

		m_box.top += m_speed;
		if( GetRect().intersects(m_objectsSolid[i].rect))
		{
			m_box.top -= m_speed;
		}
		m_box.top -= m_speed;

		m_box.left += m_speed;
		if(GetRect().intersects(m_objectsSolid[i].rect) )
		{
			m_box.left -= m_speed;
		}
		m_box.left -= m_speed;

		m_box.left -= m_speed;
		if(GetRect().intersects(m_objectsSolid[i].rect) )
		{
			m_box.left += m_speed;
		}
		m_box.left += m_speed;

		m_box.top -= m_speed;
		if(GetRect().intersects(m_objectsSolid[i].rect) )
		{
			m_box.top += m_speed;
		}
		m_box.top += m_speed;
	}
	
	for(int i = 0; i < 1; i++) 
	{

		m_box.top += m_speed;
		if(GetRect().intersects(enemyRect) )
		{
			m_box.top -= m_speed;
		}
		m_box.top -= m_speed;

		m_box.left += m_speed;
		if(GetRect().intersects(enemyRect) )
		{
			m_box.left -= m_speed;
		}
		m_box.left -= m_speed;

		m_box.left -= m_speed;
		if(GetRect().intersects(enemyRect) )
		{
			m_box.left += m_speed;
		}
		m_box.left += m_speed;

		m_box.top -= m_speed;
		if(GetRect().intersects(enemyRect) )
		{
			m_box.top += m_speed;
		}
		m_box.top += m_speed;
	}
	
}
//-------------------------------------------------------
// ProgressBar
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