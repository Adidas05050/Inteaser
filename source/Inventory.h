#ifndef INVENTORY_H
#define INVENTORY_H
#include "SFML.hpp"

class Inventory {
	public:
		Inventory();
		void drawMission(sf::RenderWindow* Window, sf::View* view);
		void drawInventory(sf::RenderWindow* Window, sf::View* view);
		void counterItem(int id);
		int checkInventory(int id, int count);
		int getCurrentMission(int x);
		std::string getTextMission(int mission);
		const int MAX_ITEM = 9;
	private:
		
		int countItem;
		int *itemInventory = new int [MAX_ITEM];
		sf::Sprite *sItem = new sf::Sprite [MAX_ITEM];
		sf::Texture *tItem = new sf::Texture [MAX_ITEM];
		sf::IntRect *mBoxItem= new sf::IntRect [MAX_ITEM];
		
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
