#ifndef TAPPLICATION_HEADER
#define TAPPLICATION_HEADER

#include <iostream>
#include <fstream>
#include <string>
#include "SFML.hpp"
#include "Tile.h"
#include "Player.h"
#include "Inventory.h"

class TApplication {

	protected:
		sf::RenderWindow *Window;
		Tile *tiles[TOTAL_TILES];
		Player *player;
		Inventory *inventory;
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
