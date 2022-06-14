#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Music.h"
#include "Skelet.h"


class Player : public Entity, public Music 
{
public:
	Player(float x, float y, int health, int speed, Tile *level, sf::RenderWindow* window);

		// События каждый кадр
	void OnFrame(sf::View* view) override;

		 // Отрисовка на экране
	void Draw(float scaleX, float scaleY);
			
		 // Перемещение персонажа
	void Move(const std::vector<Skelet*>& entities);

		 // Проверка столкновений с объектами
	void Collision(const std::vector<Skelet*>& entities);

		 // Раздача снижающая прочность
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

	void CollisionAttack(const std::vector<Skelet*>&);

	std::vector<TmxObject> m_objectsSound;
		
	float	m_decreaseFood = 1;

	// Хранит в себе анимации. Действие - направление
	std::map <AnimState, std::vector<sf::Texture>>	m_animationState; 
	std::vector<int>								m_spritesInAnimation;

	sf::Sprite	m_playerSprite;
	int			m_currentRow = 0;
	int			m_currentColumn = 0;

	ProgressBar* m_healthBar = nullptr;
	ProgressBar* m_foodBar	 = nullptr;
};

#endif
