#include "Interactions.h"
#include <iostream>
#include "SFML.hpp"

Interactions::Interactions() {
	circ.setRadius(4);
	circ.setOrigin(2, 2);
	
	item.setRadius(2);
	item.setOrigin(1, 1);
	item.setFillColor(sf::Color(0, 255, 0));
	
	fontForInteractibleObject.loadFromFile("font/single_day.ttf");
	
	textForInteractibleObject.setFont(fontForInteractibleObject);
	textForInteractibleObject.setString("Take (Press \"E\")");
	textForInteractibleObject.setFillColor(sf::Color(235, 235, 235, 0));
	textForInteractibleObject.setCharacterSize(20);
}

int Interactions::Interact(Player* player, Tile *level) {
	
	if(Interactions::idLocation == -1) {
		return -1;
	}
	
	interactTrigger.left = player->GetRect().left + player->GetRect().width / 2 - (INTERACT_TRIGGER_WIDTH / 2);
	interactTrigger.top = player->GetRect().top + player->GetRect().height / 2 - (INTERACT_TRIGGER_HEIGHT / 2);
	interactTrigger.width = INTERACT_TRIGGER_WIDTH;
	interactTrigger.height = INTERACT_TRIGGER_HEIGHT;
	
	//add new objects in the locations by the name
	interactingObjects[0] = level->GetAllObjects("interact_coast");// <<-- all objects in this location here
	interactingObjects[1] = level->GetAllObjects("interact_1st_floor");// <<-- all objects in this location here
	
	//==================================================== TRIGGER ZONE DRAW ===============================================================
	
	//IMPORTANT!!! circ, item, recta - draw some elements for the test !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	circ.setPosition(player->GetRect().left + player->GetRect().width / 2, player->GetRect().top + player->GetRect().height / 2);
	
	item.setPosition(player->GetRect().left + player->GetRect().width / 2, player->GetRect().top + player->GetRect().height / 2);
	
	recta.setSize(sf::Vector2f(interactTrigger.width, interactTrigger.height));
	recta.setOrigin(sf::Vector2f(interactTrigger.width / 2, interactTrigger.height / 2));
	recta.setOutlineThickness(-1);
	recta.setFillColor(sf::Color(0, 0, 0, 0));
	recta.setOutlineColor(sf::Color(255, 0, 0));
	recta.setPosition(sf::Vector2f(player->GetRect().left + player->GetRect().width / 2, player->GetRect().top + player->GetRect().height / 2));

	textForInteractibleObject.setFillColor(sf::Color(235, 235, 235, 0));
	//======================================================================================================================================
	
	float temp_distance = -1, temp = -1;
	close_object = -1;
	
	for(int i = 0; i < interactingObjects[idLocation].size(); i++) {
		if(interactTrigger.intersects(interactingObjects[idLocation][i].rect)) {
				
			temp = sqrt(
			(interactingObjects[idLocation][i].rect.left + interactingObjects[idLocation][i].rect.width / 2 - (player->GetRect().left + player->GetRect().width / 2)) *
			(interactingObjects[idLocation][i].rect.left + interactingObjects[idLocation][i].rect.width / 2 - (player->GetRect().left + player->GetRect().width / 2)) +
			(interactingObjects[Interactions::idLocation][i].rect.top + interactingObjects[idLocation][i].rect.height / 2 - (player->GetRect().top + player->GetRect().height / 2)) *
			(interactingObjects[Interactions::idLocation][i].rect.top + interactingObjects[idLocation][i].rect.height / 2 - (player->GetRect().top + player->GetRect().height / 2)));
			
			if(temp_distance == -1 && close_object == -1 || temp_distance > temp) {
				temp_distance = temp;
				close_object = i;
				continue;
			}	
		}
	}
	
	if(close_object != -1) {
		item.setPosition(interactingObjects[idLocation][close_object].rect.left + interactingObjects[idLocation][close_object].rect.width / 2,
		interactingObjects[idLocation][close_object].rect.top + interactingObjects[idLocation][close_object].rect.height / 2 );
		
		textForInteractibleObject.setFillColor(sf::Color(235, 235, 235, 255));
		
		textForInteractibleObject.setPosition(interactingObjects[idLocation][close_object].rect.left + interactingObjects[idLocation][close_object].rect.width / 2 - 60,
		interactingObjects[idLocation][close_object].rect.top - interactingObjects[idLocation][close_object].rect.height / 2 - 20);

		//approximate coordinates of the nearest object in the interaction zone || NEED MORE TESTS!
		// X = interactingObjects[idLocation][close_object].rect.left + interactingObjects[idLocation][close_object].rect.width / 2
		// y = interactingObjects[idLocation][close_object].rect.top - interactingObjects[idLocation][close_object].rect.height * 1.5
		
		if(player->IsInteract() && !press_check) {
			press_check = true;
			switch(close_object) {
				case 0: {	// don't touch this, because I did it to show you how each object can be unique !!!!!!!!!
					std::cout << "You are looking at the object with ID 0\n";
					return 0;
				}
				case 1: {
					std::cout << "You are looking at the object with ID 1\n";
					return 1;
				}
				case 2: {
					std::cout << "You are looking at the object with ID 2\n";
					return 2;
				}
				case 3: {
					std::cout << "You are looking at the object with ID 3\n";
					return 3;
				}
			}
		} else {
			if(press_check && !player->IsInteract()) press_check = false;
		}
	}
	return -1;
}
