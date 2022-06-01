#include "Skelet.h"
#include "header.h"

Skelet::Skelet(int health, int speed, Tile *level) {
	m_box.left = 41;
	m_box.top = 42;
	m_box.width = 80*3;
	m_box.height = 80*3;
	m_frameStep = 80;
	
	m_health = health;
	m_speed = speed;

	m_texture.loadFromFile("media/enemy/AxeBanditIdle.png");
	AnimState.push_back(m_texture);
	m_texture.loadFromFile("media/enemy/AxeBanditRun.png");
	AnimState.push_back(m_texture);
	m_texture.loadFromFile("media/enemy/AxeBanditAttack.png");
	AnimState.push_back(m_texture);
	m_objectsSolid = level->GetAllObjects("wall");
	mObjectSound = level->GetAllObjects("sound");
}
//-------------------------------------------------------
void Skelet::OnFrame(sf::View* view)
{
	m_frame++;
	Animation();

	sf::RectangleShape recta;
	recta.setSize(sf::Vector2f(m_box.width, m_box.height));
	recta.setOrigin(sf::Vector2f(m_box.width / 2, m_box.height / 2));
	recta.setOutlineThickness(-1);
	recta.setFillColor(sf::Color(0, 0, 0, 0));
	recta.setOutlineColor(sf::Color(255, 0, 0));
	recta.setPosition(sf::Vector2f(GetRect().left + GetRect().width / 2, GetRect().top + GetRect().height / 2));

	g_window->draw(recta);
}
//-------------------------------------------------------
void Skelet::spawn(int x, int y, int health) {
	m_sprite.setPosition(x, y);
	m_box.left = x;
	m_box.top = y;
	m_health = 100;
}
//-------------------------------------------------------
void Skelet::draw(float scaleX, float scaleY) {
	float width = scaleX * m_box.width;
	float height = scaleY * m_box.height;
	float skeletWidth = width / (float) m_box.width;
	float skeletHeight = height / (float) m_box.height;
	m_sprite.setScale(skeletWidth, skeletHeight);
	m_sprite.setPosition(m_box.left, m_box.top);

	if(m_box.left != -1 )
		g_window->draw(m_sprite);
}
//-------------------------------------------------------
void Skelet::Move(sf::Vector2f playerCenter)
{
	m_isStay = true;

	// Пока что так: игрок далеко стоим чилим
	if(Math::GetDistance(playerCenter.x, playerCenter.y, GetCenter().x, GetCenter().y) > 200)
		return;

	if(Math::GetDistance(playerCenter.x, playerCenter.y, GetCenter().x, GetCenter().y) < 50)
		return;

	if (playerCenter.x < GetCenter().x - m_box.width)
	{
		m_box.left -= m_speed;
		m_isLeftDirection = true;
		m_isStay = false;
	}
	if (playerCenter.x > GetCenter().x + m_box.width)
	{
		m_box.left += m_speed;
		m_isLeftDirection = false;
		m_isStay = false;
	}
	if (playerCenter.y < GetCenter().y - m_box.height)
	{
		m_box.top -= m_speed;
		m_isStay = false;
	}
	if (playerCenter.y > GetCenter().y + m_box.height)
	{
		m_box.top += m_speed;
		m_isStay = false;
	}
}
//-------------------------------------------------------
void Skelet::Animation()
{
	if (m_isStay)
	{
		m_sprite.setTexture(AnimState[int (AnimState::Idle)]);
		if (m_frame >= 6)
			m_frame = 0;
	}
	else
	{
		m_sprite.setTexture(AnimState[int(AnimState::Walk)]);
		if (m_frame >= 8)
			m_frame = 0;
	}
	if (m_isLeftDirection)
		m_sprite.setTextureRect(sf::IntRect(m_frameStep * int(m_frame) + m_frameStep, 0, -m_frameStep, m_frameStep));
	else
		m_sprite.setTextureRect(sf::IntRect(m_frameStep * int(m_frame), 0, m_frameStep, m_frameStep));
}

