#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Music.h"


class Player : public Entity, public Music 
{
public:
	Player(int x, int y, int health, int speed, Tile *level, sf::RenderWindow* window);

		// События каждый кадр
	void OnFrame(sf::View* view) override;

		 // Отрисовка на экране
	void Draw(float scaleX, float scaleY);
			
		 // Перемещение персонажа
	void Move(sf::FloatRect enemyRect);

	// Проверка столкновений с объектами
	void Сollision(sf::FloatRect enemyRect);

	void Attack() override;

	void CollisionSound();

		 // Взаимодействует ли персонаж сейчас?
	bool IsInteract() const { return m_pickUpState == ActionState::Running; }

	const int PLAYER_WIDTH = 64;
	const int PLAYER_HEIGHT = 64;
	const int PLAYER_FRAME = 8;

private:

	void LoadImages();
	void ResetAnimation();

	void PickUp();

	std::vector<TmxObject> m_objectsSound;
		
	float	m_decreaseFood = 1;

	// Хранит в себе анимации. Действие - направление
	std::map <AnimState, std::vector<sf::Texture>>	m_animationState; 
	std::vector<int>								m_spritesInAnimation;

	sf::Sprite	m_playerSprite;
	int			m_currentSpriteTile = 0;
	int			m_currentRow = 0;
	int			m_currentColumn = 0;

	// Структура для различных прогресс-баров: еда, здоровье и т.п.
	struct ProgressBar
	{
	public:
		ProgressBar(sf::Vector2f size, sf::Color color);
		void SetProgress(float progress);
		void SetColor(sf::Color color);
		void SetPosition(sf::Vector2f position);
		void Draw(sf::View* view);
	private:
		sf::Color			m_defaultColor;
		sf::RectangleShape	m_background;
		sf::RectangleShape	m_foreground;
		sf::Vector2f		m_position;
	};

	ProgressBar* m_healthBar = nullptr;
	ProgressBar* m_foodBar	 = nullptr;
};

#endif
