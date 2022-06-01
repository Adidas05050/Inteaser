#ifndef ENTITY_H
#define ENTITY_H

#include "SFML.hpp"
#include "Tile.h"

class Entity
{
public:

			// Получить текущее здоровье
	int		GetHealth();

			// Получить текущую скорость
	int		GetSpeed();
	
			// Получить координаты и размер сущности 
	auto	GetRect() -> sf::FloatRect;

			// Возвращает центр спрайта		
	auto	GetCenter() -> sf::Vector2f;

			// Жива ли сущность
	bool	IsAlive();

					// Атакующие действия	
	virtual void	Attack() = 0;

				 // Событие происходящее на каждом кадре
	virtual void OnFrame(sf::View* view) = 0;

protected:
	float m_curSpeed = 0;
	float m_speed = 0;
	int m_frame = 0;
	float m_health = 0;
	float m_maxHealth = 100;
	float m_food = 100;
	float m_maxFood = 100;

	sf::FloatRect m_box;
	sf::Texture m_texture;

	sf::RenderWindow* m_window = nullptr;

	std::vector<TmxObject> m_objectsSolid; // Список объектов, которые коллизятся с сущностью
};

#endif
