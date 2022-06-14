#ifndef TAPPLICATION_HEADER
#define TAPPLICATION_HEADER

#include "SFML.hpp"
#include "Tile.h"
#include "Player.h"
#include "Inventory.h"
#include "Music.h"
#include "ControlLight.h"
#include "Interactions.h"
#include "Skelet.h"

class TApplication 
{
public:
	TApplication();
	void Init();
	void StartLevel(int level);
	void Run();
	void CheckPortal();
	void End();
	void setInventory();
	void SmoothCamera();
	void GuiView();

private:
	sf::Vector2f m_viewPosition;

	Inventory *inventory;
	std::vector<Tile> levels;
	int m_currentLevel = 2;
	std::vector<int> enemiesInLevels;
	int enemiesInLevelRemained = 0;
	bool m_isUsedPortal = false;
	Player *player;
	std::vector<Skelet*> m_enemies;
	Music *musicControl;
	ControlLight *interface;
	Interactions *Interaction;
	sf::View m_heroView;
	sf::View m_guiView;
	sf::View miniMap;
	sf::Font font;
	sf::Text textMission;
	sf::Text Tips;
	bool m_isShowTips = true;
};
#endif
