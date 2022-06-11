#ifndef SKELET_H
#define SKELET_H

#include "Entity.h"
#include "Music.h"

class Skelet : public Entity {
public:
	Skelet(float health, float speed, Tile *level);
	void spawn(float x, float y, int health);
	void draw(float scaleX, float scaleY);
	void OnFrame(sf::View* view) override;
	void Move(sf::Vector2f playerCenter);
	void Attack() override {};
	void Animation();

protected:
	std::vector<TmxObject> mObjectSound;

	ProgressBar* m_healthBar = nullptr;
};

#endif
