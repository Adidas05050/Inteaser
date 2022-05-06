#include "skelet.h"
#include "header.h"

Skelet::Skelet(int health, int speed, Tile *level) {
	m_box.left = -1;
	m_box.top = -1;
	m_box.width = 24;
	m_box.height = 24;

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
	sSkelet.setPosition(m_box.left, m_box.top);

	if(m_box.left != -1 )
		Window->draw(sSkelet);
}

void Skelet::Move(sf::Vector2f playerCenter)
{
	// Пока что так: игрок далеко стоим чилим
	if(Math::GetDistance(playerCenter.x, playerCenter.y, GetCenter().x, GetCenter().y) > 200)
		return;

	if(Math::GetDistance(playerCenter.x, playerCenter.y, GetCenter().x, GetCenter().y) < 50)
		return;

	m_frame++;
	if (playerCenter.x < GetCenter().x - m_box.width)
	{
		m_box.left -= m_speed;
	}
	if (playerCenter.x > GetCenter().x + m_box.width)
	{
		m_box.left += m_speed;
	}
	if (playerCenter.y < GetCenter().y - m_box.height)
	{
		m_box.top -= m_speed;
	}
	if (playerCenter.y > GetCenter().y + m_box.height)
	{
		m_box.top += m_speed;
	}
}