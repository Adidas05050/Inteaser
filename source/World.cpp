#include "World.h"
#include <vector>

World::World()
{
	srand(time(nullptr));

	m_tick = 0.1f;
	m_time = 6.f;
}
//---------------------------------------------
void World::OnFrame(sf::RenderWindow* Window, sf::View* view)
{
	if (m_time > 20)
	{
		m_tick = -m_tick;
	}
	else if (m_time < 2)
	{
		m_tick = -m_tick;
	}

	// Управление дождём
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		m_isRain = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		m_isRain = false;

	// Управление временем суток
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		m_isTickingTime = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
		m_isTickingTime = false;

	if (m_isRain)
		m_rain.PlaySound();
	else
		m_rain.StopSound();

	m_rain.OnFrame(Window, view); // Всегда обрабатывается для плавного нарастания и затухания

	if(m_isTickingTime)
		m_time += m_tick; 
}

