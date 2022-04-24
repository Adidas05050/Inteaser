#include "World.h"
#include <vector>

World::World()
{
	srand(time(0));

	m_tick = 0.1;
	m_time = 6.f;

	for (int i = 0; i < 200; i++)
	{
		m_rainShapes.push_back(new RainShapes);
	}

	m_rainBuffer.loadFromFile("sounds/world/rain.ogg");
	m_rain.setBuffer(m_rainBuffer);
	m_rain.setLoop(true);
}

void World::OnFrame()
{
	if (m_time > 20)
	{
		m_tick = -m_tick;
		m_isRain = true;
	}
	else if (m_time < 2)
	{
		m_tick = -m_tick;
		m_isRain = true;
	}

	m_time += m_tick;
}

void World::DrawRain(sf::RenderWindow* Window, sf::View* view)
{
	if (!m_isRain)
	{
		m_rain.stop();
		m_isRainPlaying = false;
		return;
	}

	if (!m_isRainPlaying)
	{
		m_rain.play();
		m_isRainPlaying = true;
	}

	for (const auto& rainShape : m_rainShapes)
	{
		rainShape->Move();
		rainShape->SetPosition(view);
		Window->draw(*rainShape->GetShape());
	}
}

RainShapes::RainShapes()
{
	m_x = rand() % 800 + 1;
	m_y = rand() % 600 + 1;
	m_dy = 1;
	m_moveSpeed = 30;
	m_rainShape = new sf::RectangleShape(sf::Vector2f(1, 10));
	m_rainShape->setFillColor(sf::Color(120, 120, 220, 100));
	m_rainShape->setPosition(m_x, m_y);
}

void RainShapes::Move()
{
	if (m_y > 600)
		m_y = rand() % -50;

	m_y += m_dy * m_moveSpeed;
}

void RainShapes::SetPosition(sf::View* view)
{
	const auto& coordBegin = view->getCenter() - view->getSize() / 2.f;
	m_rainShape->setPosition(sf::Vector2f(m_x + coordBegin.x, m_y + coordBegin.y - 20));
}

sf::RectangleShape* RainShapes::GetShape() const
{
	return m_rainShape;
}