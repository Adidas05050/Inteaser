#pragma once
#include "SFML.hpp"

class RainShapes;

class World
{
public:
	World();
	float GetTime() { return m_time; }
	void OnFrame();
	void DrawRain(sf::RenderWindow* Window, sf::View* view);

private:
	float m_time, m_tick;
	bool m_isRain = false;
	std::vector <RainShapes*> m_rainShapes;
};

class RainShapes
{
public:
	RainShapes();
	void Move();
	void SetPosition(sf::View* view);
	sf::RectangleShape* GetShape() const;

private:
	sf::RectangleShape* m_rainShape;
	int m_x, m_y, m_dy, m_moveSpeed;
};