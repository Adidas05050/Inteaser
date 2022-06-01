#ifndef TAPPLICATION_HEADER
#define TAPPLICATION_HEADER

#include "SFML.hpp"
#include "Tile.h"
#include "Player.h"
#include "Inventory.h"
#include "Music.h"
#include "ControlLight.h"
#include "Interactions.h"
#include "skelet.h"

class TApplication 
{
public:
	TApplication();
	void Init();
	void Run();
	void End();
	void setInventory();
	void SmoothCamera();
	void GuiView();

private:
	sf::Vector2f m_viewPosition;

	Inventory *inventory;
	Tile *level;
	Player *player;
	Skelet *skelet;
	Music *musicControl;
	ControlLight *interface;
	Interactions *Interaction;
	sf::View m_heroView;
	sf::View m_guiView;
	sf::View miniMap;
	sf::Font font;
	sf::Text textMission;
};
#endif
