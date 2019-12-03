#ifndef TAPPLICATION_HEADER
#define TAPPLICATION_HEADER
 
#include "SFML.hpp"
#include "TMapWidget.h"
#include "Player.h"


class TApplication {
	
     protected:
        sf::RenderWindow *Window;
        TMapWidget *MapWidget;
        Player *player;

     public:
		TApplication();
		void Init();
		void Run();
		void End();
};
 
#endif
