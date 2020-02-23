#ifndef TAPPLICATION_HEADER
#define TAPPLICATION_HEADER

#include <iostream>
#include <fstream>
#include <string>
#include "SFML.hpp"
#include "Tile.h"
#include "Player.h"
#include "Inventory.h"
#include "Music.h"
#include "Interface.h"
#include "Interactions.h"

class TApplication {

	protected:
		sf::RenderWindow *Window;
		Inventory *inventory;
		Tile *level;
		Player *player;
		Music *musicControl;
		Interface *interface;
		Interactions *Interaction;
		sf::View heroView;
		sf::View miniMap;
		sf::Font font;
		sf::Text textMission;

	public:
		TApplication();
		void Init();
		void Run();
		void End();
		void setInventory();
};

#endif
