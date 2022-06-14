#include "Skelet.h"
#include "header.h"
namespace
{
	const float EntityBoxWidth = -70;
	const float EntityBoxHeight = -60;
}
Skelet::Skelet(float health, float speed, Tile *level, Type type) {
	m_box.left = EntityBoxWidth;
	m_box.top = EntityBoxHeight;
	m_box.width = 20;
	m_box.height = 20;
	m_frameStep = 80;
	m_type = type;
	m_health = health;
	m_maxHealth = health;
	m_speed = speed;
	if (type == Type::Bandit)
	{
		m_texture.loadFromFile("media/enemy/AxeBanditIdle.png");
		m_animState.push_back(m_texture);
		m_texture.loadFromFile("media/enemy/AxeBanditRun.png");
		m_animState.push_back(m_texture);
		m_texture.loadFromFile("media/enemy/AxeBanditAttack.png");
		m_animState.push_back(m_texture);
	}
	else if(type == Type::Ara)
	{
		m_texture.loadFromFile("media/enemy/Ara80.png");
		m_animState.push_back(m_texture);
		m_texture.loadFromFile("media/enemy/Ara80.png");
		m_animState.push_back(m_texture);
		m_texture.loadFromFile("media/enemy/Ara80.png");
		m_animState.push_back(m_texture);
	}
	m_objectsSolid = level->GetAllObjects("wall");
	mObjectSound = level->GetAllObjects("sound");

	m_healthBar = new ProgressBar(sf::Vector2f(20, 5), sf::Color::Red);

	m_healthBar->SetProgress(m_health / m_maxHealth);
}
//-------------------------------------------------------
void Skelet::OnFrame(sf::View* view)
{
	if (m_frame > 64)
		m_frame = 0;

	if (m_frame % 4 == 0)
		m_currentSpriteTile++;

	Animation();
	Attack();
	// Collision box
	sf::RectangleShape recta;
	recta.setSize(sf::Vector2f(m_box.width, m_box.height));
	recta.setOrigin(sf::Vector2f(m_box.width / 2, m_box.height / 2));
	recta.setOutlineThickness(-1);
	recta.setFillColor(sf::Color(0, 0, 0, 0));
	recta.setOutlineColor(IsAlive() ? sf::Color(255, 0, 0) : sf::Color(0, 0, 0));
	recta.setPosition(sf::Vector2f(m_box.left + m_box.width / 2, m_box.top + m_box.height / 2));

	g_window->draw(recta);
	// //

	m_frame++;
}
//-------------------------------------------------------
void Skelet::spawn(Entity* player, float x, float y, int health) {
	m_collisionEntities.push_back(player);
	m_sprite.setPosition(x, y);
	m_box.left = x;
	m_box.top = y;
	m_health = health;
	m_positionSprite = { x, y };
}
//-------------------------------------------------------
void Skelet::draw(float scaleX, float scaleY) {
	float width = scaleX * m_box.width;
	float height = scaleY * m_box.height;
	float skeletWidth = width / (float) m_box.width;
	float skeletHeight = height / (float) m_box.height;
	m_sprite.setScale(skeletWidth, skeletHeight);

	m_sprite.setPosition(m_positionSprite);
	
	if(m_box.left != -1 )
		g_window->draw(m_sprite);

	m_healthBar->SetProgress(m_health / m_maxHealth);
	m_healthBar->SetPosition(sf::Vector2f(m_box.left, m_box.top - 10));
	m_healthBar->Draw();
}
//-------------------------------------------------------
void Skelet::Move(sf::Vector2f playerCenter)
{
	// Мёртвые не ходят, только если нет особой логики
	if (!IsAlive())
		return;
	m_curSpeed = m_speed;
	m_isStay = true;

	// Пока что так: игрок далеко стоим чилим
	if(Math::GetDistance(playerCenter.x, playerCenter.y, GetCenter().x, GetCenter().y) > (m_type == Type::Bandit ? 200 : 500))
		return;

	if(Math::GetDistance(playerCenter.x, playerCenter.y, GetCenter().x, GetCenter().y) < 47)
		return;

	sf::IntRect direction = CollisionSimple();
	if (direction.top && playerCenter.y < GetCenter().y)
		return;
	if (direction.height && playerCenter.y > GetCenter().y)
		return;
	if (direction.width && playerCenter.x > GetCenter().x)
		return;
	if (direction.left && playerCenter.x < GetCenter().x)
		return;

	if (!direction.left && playerCenter.x < GetCenter().x - m_box.width)
	{
		m_box.left -= m_speed;
		m_isLeftDirection = true;
		m_isStay = false;
	}
	if (!direction.width && playerCenter.x > GetCenter().x + m_box.width)
	{
		m_box.left += m_speed;
		m_isLeftDirection = false;
		m_isStay = false;
	}
	if (!direction.top && playerCenter.y < GetCenter().y - m_box.height)
	{
		m_box.top -= m_speed;
		m_isStay = false;
	}
	if (!direction.height && playerCenter.y > GetCenter().y + m_box.height)
	{
		m_box.top += m_speed;
		m_isStay = false;
	}

	
}
//-------------------------------------------------------
void Skelet::Attack()
{
	if (m_attackState == ActionState::Ended)
		m_attackState = ActionState::Idle;

	if (!IsAlive())
		return;

	if (!m_canAttack && m_frame % 20 == 0)
		m_canAttack = true;

	if(m_collisionEntities.empty() )
		return;

	for (const auto& enemy : m_collisionEntities)
	{
		if (m_canAttack && Math::GetDistance(enemy->GetCenter().x, enemy->GetCenter().y, GetCenter().x, GetCenter().y) < 47)
		{
			m_attackState = ActionState::Running;
			m_canAttack = false;
			enemy->SetDamage(5.f);
		}
	}

}
//-------------------------------------------------------
void Skelet::Animation()
{
	m_positionSprite.x = m_box.left + EntityBoxWidth;
	m_positionSprite.y = m_box.top + EntityBoxHeight;

	if (!IsAlive())
	{
		m_currentSpriteTile = 0;
		if(m_sprite.getRotation() == 0.f)
			m_sprite.rotate(90);
		m_positionSprite.x = m_box.left + m_frameStep;
	}

	if(m_attackState == ActionState::Running)
	{
		m_sprite.setTexture(m_animState[int(AnimState::Attack)]);
		if (m_type == Type::Bandit && m_currentSpriteTile >= 7)
		{
			m_attackState = ActionState::Ended;
			m_currentSpriteTile = 0;
		}
		else if (m_type == Type::Ara && m_currentSpriteTile >= 4)
		{
			m_attackState = ActionState::Ended;
			m_currentSpriteTile = 0;
		}

	}
	else if (m_isStay)
	{
		m_sprite.setTexture(m_animState[int (AnimState::Idle)]);
		if (m_type == Type::Bandit && m_currentSpriteTile >= 6)
			m_currentSpriteTile = 0;
		else if (m_type == Type::Ara && m_currentSpriteTile >= 4)
			m_currentSpriteTile = 0;
	}
	else
	{
		m_sprite.setTexture(m_animState[int(AnimState::Walk)]);
		if (m_type == Type::Bandit && m_currentSpriteTile >= 8)
			m_currentSpriteTile = 0;
		else if (m_type == Type::Ara && m_currentSpriteTile >= 4)
			m_currentSpriteTile = 0;
	}
	if (m_isLeftDirection)
		m_sprite.setTextureRect(sf::IntRect(m_frameStep * int(m_currentSpriteTile) + m_frameStep, 0, -m_frameStep, m_frameStep));
	else
		m_sprite.setTextureRect(sf::IntRect(m_frameStep * int(m_currentSpriteTile), 0, m_frameStep, m_frameStep));
}
//-------------------------------------------------------

