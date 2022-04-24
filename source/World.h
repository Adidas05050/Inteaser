#pragma once
#include "SFML.hpp"

class RainShapes;

class World
{
public:
	World();

	float	GetTime() { return m_time; }
	void	OnFrame();
	void	DrawRain(sf::RenderWindow* Window, sf::View* view);

private:
	float	m_time;
	float	m_tick;
	bool	m_isRain = false;
	bool	m_isRainPlaying = false;

	std::vector <RainShapes*> m_rainShapes;

	sf::SoundBuffer m_rainBuffer;
	sf::Sound m_rain;
};

class RainShapes
{
public:
	RainShapes();
	void	Move();
	void	SetPosition(sf::View* view);
	auto	GetShape() const->sf::RectangleShape*;

private:
	int		m_x;
	int		m_y;
	int		m_dy;
	int		m_moveSpeed;

	sf::RectangleShape* m_rainShape;
};