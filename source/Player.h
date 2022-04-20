#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Music.h"


class Player : public Entity, public Music 
{
public:
	Player(int x, int y, int health, int speed, Tile *level, sf::RenderWindow* window);
	void draw(sf::RenderWindow* Window, int scaleX, int scaleY);
	void move();
	void collision(sf::FloatRect enemyRect);
	void collisionSound();
	void OnFrame(sf::RenderWindow* Window, sf::View* view) override;
	const int PLAYER_WIDTH = 24;
	const int PLAYER_HEIGHT = 24;
	const int PLAYER_FRAME = 8;

private:
	std::vector<TmxObject> mObjectSound;
		
	float m_decreaseFood = 1;
	sf::Sprite sPlayer;
	int	mSpriteTile;
	float mScale;
	sf::Vector2i forJump;
	bool canJump = true;
	bool inAir = false;
	bool isLeftDirection = false;
	bool isStay = true;


	struct ProgressBar
	{
	public:
		ProgressBar(sf::Vector2f size, sf::Color color);
		void SetProgress(float progress);
		void SetColor(sf::Color color);
		void SetPosition(sf::Vector2f position);
		void Draw(sf::RenderWindow* window, sf::View* view);
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
