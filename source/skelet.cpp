#include "skelet.h"

Skelet::Skelet(int health, int speed, Tile *level) {
	m_box.left = -1;
	m_box.top = -1;
	m_box.width = 24;
	m_box.height = 48;

	m_health = health;
	m_speed = speed;

	m_texture.loadFromFile("media/enemy/skelet.png");
	sSkelet.setTexture(m_texture);
	m_objectsSolid = level->GetAllObjects("wall");
	mObjectSound = level->GetAllObjects("sound");
}

void Skelet::spawn(int x, int y, int health) {
	sSkelet.setPosition(x, y);
	m_box.left = x;
	m_box.top = y;
	m_health = 100;
}

void Skelet::draw(sf::RenderWindow* Window, float scaleX, float scaleY) {
	float width = scaleX * m_box.width;
	float height = scaleY * m_box.height;
	float skeletWidth = width / (float) m_box.width;
	float skeletHeight = height / (float) m_box.height;
	sSkelet.setScale(skeletWidth, skeletHeight);
	if(m_box.left != -1 )
		Window->draw(sSkelet);
}

void Skelet::Move(sf::Vector2f playerRect)
{
	m_frame++;
	if (playerRect.x < GetCenter().x)
	{
		m_box.left -= m_speed;
	}
	if (playerRect.x > GetCenter().x)
	{
		m_box.left += m_speed;
	}
	if (playerRect.y < GetCenter().y)
	{
		m_box.left += m_speed;
	}
	if (playerRect.y > GetCenter().y)
	{
		m_box.left -= m_speed;
	}
}