//---------------------------------------------
// ����� ��� �������� �����.
// ������ ������������ Rain
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

			// ������� ������ ����, ����� ��� �����
	void	OnFrame(sf::RenderWindow* Window, sf::View* view);

			// ���������� ������ �����
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
			// ��������� ������� ����������� / ���������� �����
	void	SmoothRainControl(); 

	float m_currentSpeedRain = 0.f; // [0..1] ������� ��������, �� �� ������� ���-�� ������ ����� �� ������
	float m_speedGainRain = 0.001f; // ��������, � ������� ����� �� ������ ������������ � �����

	bool			m_isRainPlaying = false;
	sf::SoundBuffer m_rainBuffer;
	sf::Sound		m_rainSound;
};
//---------------------------------------------
};
