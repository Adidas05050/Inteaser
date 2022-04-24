//---------------------------------------------
// Класс для описания погод.
// Сейчас используется Rain
//---------------------------------------------
#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace Weather
{
//---------------------------------------------
class Rain
{
public:
	Rain();

			// События каждый кадр, когда идёт дождь
	void	OnFrame(sf::RenderWindow* Window, sf::View* view);

			// Управление звуком дождя
	void	PlaySound();
	void	StopSound();

	struct RainShapes
	{
	public:
		RainShapes();
		void	Move();
		void	SetPosition(sf::View* view);
		auto	GetShape() const -> const sf::RectangleShape&;

	private:
		int		m_x;
		int		m_y;
		int		m_dy;
		int		m_moveSpeed;

		sf::RectangleShape m_rainShape;
	};

	std::vector <RainShapes*> m_rainShapes;
private:
			// Управляет плавным наростанием / затуханием дождя
	void	SmoothRainControl(); 

	float m_currentSpeedRain = 0.f; // [0..1] Текущая скорость, от неё зависит кол-во капель дождя на экране
	float m_speedGainRain = 0.001f; // Скорость, с которой дождь из ничего превращается в ДОЖДЬ

	bool			m_isRainPlaying = false;
	sf::SoundBuffer m_rainBuffer;
	sf::Sound		m_rainSound;
};
//---------------------------------------------
};
