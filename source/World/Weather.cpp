#include "Weather.h"

#include <SFML/Audio/SoundBuffer.hpp>

namespace Weather
{
//---------------------------------------------
Rain::Rain()
{
	for (int i = 0; i < 200; i++)
	{
		m_rainShapes.push_back(new RainShapes);
	}

	m_rainBuffer.loadFromFile("sounds/world/rain.ogg");
	m_rainSound.setBuffer(m_rainBuffer);
	m_rainSound.setLoop(true);
	m_isRainPlaying = false;

}
//---------------------------------------------
void Rain::OnFrame(sf::RenderWindow* Window, sf::View* view)
{
	SmoothRainControl();
	if (m_currentSpeedRain < FLT_MIN)
		return;

	// Фишка с интенсивностью дождя
	for (int i = 0; i < static_cast<int>(m_rainShapes.size() * m_currentSpeedRain); i++)
	{
		m_rainShapes[i]->Move();
		m_rainShapes[i]->SetPosition(view);
		Window->draw(m_rainShapes[i]->GetShape());
	}
	m_rainSound.setVolume(m_currentSpeedRain * 100);
}
//---------------------------------------------
void Rain::SmoothRainControl()
{
	// Условие проверяет на нулевую текущюю скорость, чтобы включать/выключать один раз
	if(m_currentSpeedRain < FLT_MIN and m_isRainPlaying)
		m_rainSound.play();
	else if (m_currentSpeedRain < FLT_MIN and !m_isRainPlaying)
		m_rainSound.stop();

	const float speedGainRain = m_speedGainRain * (m_isRainPlaying ? 1.f : -1.f);
	m_currentSpeedRain = std::clamp(m_currentSpeedRain + speedGainRain, 0.f, 1.f);
}
//---------------------------------------------
void Rain::PlaySound()
{
	m_isRainPlaying = true;
}
//---------------------------------------------
void Rain::StopSound()
{
	m_isRainPlaying = false;
}
//---------------------------------------------
// Rain::RainShapes
//---------------------------------------------
Rain::RainShapes::RainShapes()
{
	m_x = rand() % 800 + 1;
	m_y = rand() % 600 + 1;
	m_dy = 1;
	m_moveSpeed = 30;
	m_rainShape.setSize(sf::Vector2f(1, 10));
	m_rainShape.setFillColor(sf::Color(120, 120, 220, 100));
	m_rainShape.setPosition(m_x, m_y);
}
//---------------------------------------------
void Rain::RainShapes::Move()
{
	if (m_y > 600)
		m_y = rand() % -50;

	m_y += m_dy * m_moveSpeed;
}
//---------------------------------------------
void Rain::RainShapes::SetPosition(sf::View* view)
{
	const auto& coordBegin = view->getCenter() - view->getSize() / 2.f;
	m_rainShape.setPosition(m_x + coordBegin.x, m_y + coordBegin.y - 20);
}
//---------------------------------------------
const sf::RectangleShape& Rain::RainShapes::GetShape() const
{
	return m_rainShape;
}
//---------------------------------------------
}
