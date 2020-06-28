#ifndef INTERACTION_H
#define INTERACTION_H

#include "SFML.hpp"
#include "Tile.h"
#include "Player.h"

class Interactions {
	
	public:
		static const int NUMBER_OF_OBJECTS_TO_INTERACT = 2;
		
		const float INTERACT_TRIGGER_HEIGHT = 300;// TRIGGER ZONE HEIGHT
		const float INTERACT_TRIGGER_WIDTH = 300;// TRIGGER ZONE WIDTH
		
		int Interact(Player* player, Tile *level);
		
		Interactions();
		
		int idLocation = 0;
		int close_object = -1;
		
		bool press_check = false;
		
		sf::CircleShape circ;
		sf::CircleShape item;
		sf::RectangleShape recta;
		sf::Font fontForInteractibleObject;
		sf::Text textForInteractibleObject;
		
		sf::FloatRect interactTrigger;
	
	private:
		std::vector<TmxObject> interactingObjects[NUMBER_OF_OBJECTS_TO_INTERACT];
};

#endif
