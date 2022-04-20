#ifndef ENTITY_H
#define ENTITY_H

#include "SFML.hpp"
#include "Tile.h"

class Entity {
public:
	int mSpeed = 0;
	int getHealth();
	int getSpeed();
	sf::FloatRect getRect();
	float getCenterX();
	float getCenterY();
	bool alive();
	virtual void OnFrame(sf::RenderWindow* Window, sf::View* view) = 0;
	std::vector<TmxObject> objSolid;

protected:
	int mFrame = 0;
	float mHealth = 0;
	float m_maxHealth = 100;
	float m_food = 100;
	float m_maxFood = 100;

	sf::FloatRect mBox;
	sf::Texture texture;

	sf::RenderWindow* m_window = nullptr;
};

#endif
