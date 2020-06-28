#ifndef INVENTORY_H
#define INVENTORY_H
#include "SFML.hpp"

class Inventory {
	public:
		Inventory();
		void drawMission(sf::RenderWindow* Window, sf::View* view);
		void drawInventory(sf::RenderWindow* Window, sf::View* view);
		void counterItem(int id);
		int getCurrentMission(int x);
		std::string getTextMission(int mission);

	private:
		int countItem;
		sf::Sprite sItem[9];
		sf::Texture tItem[9];
		sf::IntRect mBoxItem[9];
		
		sf::IntRect mBoxMission;
		sf::Texture tMission;
		sf::Sprite sMission;
		
		sf::IntRect mBoxInventory;
		sf::Texture tInventory;
		sf::Sprite sInventory;
		
		std::map<int, std::string> itemMap = 
		{
			{0, "lemon"},
			{1, "cs"},
			{2, "hammer"},
			{3, "coin"}
		};
};

#endif
