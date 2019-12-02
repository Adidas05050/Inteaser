#ifndef TAPPLICATION_HEADER
#define TAPPLICATION_HEADER
 
#include "SFML.hpp"
#include "TMapWidget.h"



class TApplication {
	
     protected:
        sf::RenderWindow *Window;
        TMapWidget *MapWidget;

     public:
		TApplication();
		void Init();
		void Run();
		void End();
};
 
#endif
