#pragma once
#include "SFML.hpp"
#include "World/Weather.h"

class RainShapes;

class World
{
public:
	World();

	float	GetTime() const { return m_isTickingTime? m_time : 2; }
	void	OnFrame(sf::RenderWindow* Window, sf::View* view);
	
private:
	float	m_time;
	float	m_tick;
	bool	m_isRain = false;
	bool	m_isTickingTime = true;

	Weather::Rain m_rain;
};

