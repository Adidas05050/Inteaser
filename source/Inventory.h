#ifndef INVENTORY_H
#define INVENTORY_H
#include "SFML.hpp"

class Inventory {
	public:
		Inventory(int x, int y);
		void draw(sf::RenderWindow* Window, sf::View* view);
		int getCurrentMission(int x);
		std::string getTextMission(int mission);
		int getX();
		int getY();

	private:
		sf::IntRect mBox;
		sf::Texture texture;
		sf::Sprite sInventory;
};

#endif
