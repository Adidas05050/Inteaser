#ifndef TAPPLICATION_HEADER
#define TAPPLICATION_HEADER

#include <iostream>
#include <fstream>
#include <string>
#include "SFML.hpp"
#include "Tile.h"
#include "Player.h"

class TApplication {
	
     protected:
        sf::RenderWindow *Window;
        Tile *tiles[TOTAL_TILES];
        Player *player;

     public:
		TApplication();
		void Init();
		void Run();
		void End();
};
 
#endif
