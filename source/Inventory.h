#ifndef INVENTORY_H
#define INVENTORY_H
#include "Entity.h"
#include "SFML.hpp"

class Inventory {
public:
	Inventory(Entity* player);
	void drawMission(sf::RenderWindow* Window, sf::View* view);
	void drawInventory(sf::RenderWindow* Window, sf::View* view);
	void counterItem(int id);
	void UpdateItem();
	int checkInventory(int id, int count);
	int getCurrentMission(int x);
	std::string getTextMission(int mission);
	void UseItem();
private:
	void SetCurrentItem();
	const int MAX_ITEM = 9;

	int countItem;
	std::vector<int> itemInventory = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
	sf::Sprite *sItem = new sf::Sprite [MAX_ITEM];
	sf::Texture *tItem = new sf::Texture [MAX_ITEM];
	sf::IntRect *mBoxItem= new sf::IntRect [MAX_ITEM];
	
	sf::IntRect mBoxMission;
	sf::Texture tMission;
	sf::Texture tApple;
	sf::Sprite sMission;
	
	sf::IntRect mBoxInventory;
	sf::Texture tInventory;
	sf::Sprite sInventory;

	int m_currentItem = 0;

	std::map<int, std::string> itemMap = 
	{
		{0, "apple"},
		{1, "cs"},
		{2, "hammer"},
		{3, "coin"}
	};
	Entity* player = nullptr;
};

#endif
