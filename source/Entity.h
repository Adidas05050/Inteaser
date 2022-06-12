#ifndef ENTITY_H
#define ENTITY_H

#include "SFML.hpp"
#include "Tile.h"

class Entity
{
public:

	// Получить текущее здоровье
	float	GetHealth() const;

	// Получить текущую скорость
	float	GetSpeed() const;

	// Получить координаты и размер сущности 
	auto	GetRect() const ->sf::FloatRect;

	// Выставление полученого урона
	void	SetDamage(float damage);

	// Возвращает центр спрайта		
	auto	GetCenter() const ->sf::Vector2f;

	// Жива ли сущность
	bool	IsAlive() const;

	// Атакующие действия	
	virtual void	Attack() = 0;

	// Событие происходящее на каждом кадре
	virtual void OnFrame(sf::View* view) = 0;


protected:
	float	m_curSpeed = 0;
	float	m_speed = 0;
	int		m_frame = 0;
	int		m_frameStep = 0;
	float	m_health = 0;
	float	m_maxHealth = 100;
	float	m_food = 100;
	float	m_maxFood = 100;
	bool	m_isLeftDirection = false;
	bool	m_isStay = true;
	bool	m_isWeak = false;
	int		m_currentSpriteTile = 0;
	bool	m_canAttack = true;

	Entity* m_collisionEntity = nullptr; // То с чем сейчас коллизится сущность. Возможно нужен список всех

	sf::Vector2f m_positionSprite = {0.f, 0.f};
	sf::Sprite m_sprite;
	std::vector <sf::Texture> m_animState;

	enum class AnimState
	{
		Idle,
		Walk,
		Attack,
		PickUp
	};

	enum class Direction
	{
		Up,
		Left,
		Right,
		Down
	};
	sf::IntRect Collision();
	sf::IntRect CollisionSimple();

	enum class ActionState
	{
		Idle,
		Running,
		Ended
	};

	ActionState m_attackState = ActionState::Idle;
	ActionState m_pickUpState = ActionState::Idle;
	Direction m_direction = Direction::Down;
	AnimState m_curAnimState = AnimState::Idle;

	sf::FloatRect m_box;
	sf::Texture m_texture;

	sf::RenderWindow* m_window = nullptr;

	std::vector<TmxObject> m_objectsSolid; // Список объектов, которые коллизятся с сущностью

	// Структура для различных прогресс-баров: еда, здоровье и т.п.
	struct ProgressBar
	{
	public:
		ProgressBar(sf::Vector2f size, sf::Color color);
		void SetProgress(float progress);
		void SetColor(sf::Color color);
		void SetPosition(sf::Vector2f position);
		void Draw(sf::View* view);	// На GUI
		void Draw();				// В мире
	private:
		sf::Color			m_defaultColor;
		sf::RectangleShape	m_background;
		sf::RectangleShape	m_foreground;
		sf::Vector2f		m_position;
	};
};

#endif
