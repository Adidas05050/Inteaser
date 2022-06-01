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
	void Draw(int scaleX, int scaleY);
			
		 // Перемещение персонажа
	void Move(sf::FloatRect enemyRect);

		 // Проверка столкновений с объектами
	void Сollision(sf::FloatRect enemyRect);

	void Attack() override;

	void CollisionSound();

	const int PLAYER_WIDTH = 24;
	const int PLAYER_HEIGHT = 24;
	const int PLAYER_FRAME = 8;


private:
	std::vector<TmxObject> m_objectsSound;
		
	float m_decreaseFood = 1;

	sf::Sprite m_playerSprite;
	int	m_spriteTile;
	float m_scale;
	sf::Vector2i m_forJump;
	bool m_isCanJump = true;
	bool m_isInAir = false;

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
		sf::Color m_defaultColor;
		sf::RectangleShape m_background;
		sf::RectangleShape m_foreground;
		sf::Vector2f m_position;
	};

	ProgressBar* m_healthBar = nullptr;
	ProgressBar* m_foodBar = nullptr;
};

#endif
