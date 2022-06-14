#ifndef SKELET_H
#define SKELET_H

#include "Entity.h"
#include "Music.h"

class Skelet : public Entity {
	
public:
	enum class Type
	{
		Bandit,
		Ara
	};

	Skelet(float health, float speed, Tile *level, Type type);
	void spawn(Entity* player, float x, float y, int health);
	void draw(float scaleX, float scaleY);
	void OnFrame(sf::View* view) override;
	void Move(sf::Vector2f playerCenter);
	void Attack() override;
	void Animation();

protected:
	Type m_type = Type::Bandit;
	std::vector<TmxObject> mObjectSound;

	ProgressBar* m_healthBar = nullptr;
};

#endif
