#ifndef ENTITY_H
#define ENTITY_H

#include "SFML.hpp"
#include "Tile.h"

class Entity
{
public:

			// �������� ������� ��������
	int		GetHealth();

			// �������� ������� ��������
	int		GetSpeed();
	
			// �������� ���������� � ������ �������� 
	auto	GetRect() -> sf::FloatRect;

			// ���������� ����� �������		
	auto	GetCenter() -> sf::Vector2f;

			// ���� �� ��������
	bool	IsAlive();

					// ��������� ��������	
	virtual void	Attack() = 0;

				 // ������� ������������ �� ������ �����
	virtual void OnFrame(sf::View* view) = 0;

protected:
	float m_curSpeed = 0;
	float m_speed = 0;
	int m_frame = 0;
	int m_frameStep = 0;
	float m_health = 0;
	float m_maxHealth = 100;
	float m_food = 100;
	float m_maxFood = 100;
	bool m_isLeftDirection = false;
	bool m_isStay = true;
	bool m_isWeak = false;
	bool m_isAttack = false;

	sf::Sprite m_sprite;
	std::vector <sf::Texture> AnimState;
	enum class AnimState
	{
		Idle,
		Walk,
		Attack,
		PickUp
	};

	sf::FloatRect m_box;
	sf::Texture m_texture;

	sf::RenderWindow* m_window = nullptr;

	std::vector<TmxObject> m_objectsSolid; // ������ ��������, ������� ���������� � ���������
};

#endif
