#pragma once
#include "SFML.hpp"
#include "World/Weather.h"

class RainShapes;

class World
{
public:
	World();

	float	GetTime() { return 2; }
	void	OnFrame(sf::RenderWindow* Window, sf::View* view);
	
private:
	float	m_time;
	float	m_tick;
	bool	m_isRain = false;

	Weather::Rain m_rain;
};

