#include "Entity.h"
//-------------------------------------------------------
sf::Vector2f Entity::GetCenter() const
{
	return sf::Vector2f((m_box.width / 2) + m_box.left, (m_box.height / 2) + m_box.top);
}
//-------------------------------------------------------
sf::FloatRect Entity::GetRect() const
{
	return m_box;
}
//-------------------------------------------------------
void Entity::SetDamage(float damage) 
{
	m_health = std::clamp(m_health - damage, 0.f, m_maxHealth);
}
//-------------------------------------------------------
float Entity::GetHealth() const
{
	return m_health;
}
//-------------------------------------------------------
float Entity::GetSpeed() const
{
	return m_speed;
}
//-------------------------------------------------------
bool Entity::IsAlive() const
{
	return m_health > 0;
}
//-------------------------------------------------------
// ProgressBar
//-------------------------------------------------------
Entity::ProgressBar::ProgressBar(sf::Vector2f size, sf::Color color)
{
	m_background.setSize(size);
	m_background.setFillColor(sf::Color::Black);
	m_foreground.setSize(size);
	m_foreground.setFillColor(color);
}
//-------------------------------------------------------
void Entity::ProgressBar::SetProgress(float progress)
{
	m_foreground.setScale(progress, 1.f);
}
//-------------------------------------------------------
void Entity::ProgressBar::SetColor(sf::Color color)
{
	m_foreground.setFillColor(color);
}
//-------------------------------------------------------
void Entity::ProgressBar::SetPosition(sf::Vector2f position)
{
	m_position = position;
}
//-------------------------------------------------------
void Entity::ProgressBar::Draw(sf::View* view)
{
	const auto& coordBegin = view->getCenter() - view->getSize() / 2.f;
	sf::Vector2f positionOnView = sf::Vector2f(m_position.x + coordBegin.x, m_position.y + coordBegin.y);
	m_background.setPosition(positionOnView);
	m_foreground.setPosition(positionOnView);
	g_window->draw(m_background);
	g_window->draw(m_foreground);
}
//-------------------------------------------------------
void Entity::ProgressBar::Draw()
{
	m_background.setPosition(m_position);
	m_foreground.setPosition(m_position);
	g_window->draw(m_background);
	g_window->draw(m_foreground);
}
//-------------------------------------------------------