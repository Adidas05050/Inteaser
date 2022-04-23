#include "Entity.h"
//-------------------------------------------------------
sf::Vector2f Entity::GetCenter()
{
	return sf::Vector2f((m_box.width / 2) + m_box.left, (m_box.height / 2) + m_box.top);
}
//-------------------------------------------------------
sf::FloatRect Entity::GetRect() 
{
	return m_box;
}
//-------------------------------------------------------
int Entity::GetHealth() 
{
	return m_health;
}
//-------------------------------------------------------
int Entity::GetSpeed() 
{
	return m_speed;
}
//-------------------------------------------------------
bool Entity::IsAlive() 
{
	return (m_health > 0? true: false);
}
//-------------------------------------------------------
