#include "Inventory.h"

Inventory::Inventory() {
	countItem = 0;
	//Mission init
	tMission.loadFromFile("media/background/missionbg.jpg");
	mBoxMission.width = tMission.getSize().x;
	mBoxMission.height = tMission.getSize().y;
	sMission.setTexture(tMission);
	//Inventory init
	tInventory.loadFromFile("media/background/inventory.png");
	mBoxInventory.width = tInventory.getSize().x;
	mBoxInventory.height = tInventory.getSize().y;
	sInventory.setTexture(tInventory);
}

int Inventory::checkInventory(int id, int count) {
	int needItem = 0;
	for(int i = 0; i < MAX_ITEM; i++) {
		if(itemInventory[i] == id)
			needItem++;
	}
	
	return (needItem >= count? true: false);
}
void Inventory::counterItem(int id) {
	if(id == -1)
		return;
	if(countItem < MAX_ITEM) {
		auto it = itemMap.find(id);
		if(it !=itemMap.end()) {
			tItem[countItem].loadFromFile("media/item/" + it->second + ".png");
			std::cout << it->second << '\n';
		} else {
			std::cout << "Item ID not found: " << id << std::endl;
		}
		sItem[countItem].setTexture(tItem[countItem]);
		sItem[countItem].setScale(0.06f, 0.06f);
		itemInventory[countItem] = id;
		countItem++;
	}

}

void Inventory::drawInventory(sf::RenderWindow* Window, sf::View* view) {
	//draw Inventory
	sInventory.setScale(0.7f, 0.7f);
	mBoxInventory.left = view->getCenter().x + 100;
	mBoxInventory.top = view->getCenter().y - 220;
	sInventory.setPosition(mBoxInventory.left, mBoxInventory.top);

	Window->draw(sInventory);
	for(int i = 0; i < countItem; i++) {
		mBoxItem[i].left = mBoxInventory.left + mBoxInventory.width - 19.5f*i - 93;
		mBoxItem[i].top = mBoxInventory.top + mBoxInventory.height - 28;
		sItem[i].setPosition(mBoxItem[i].left, mBoxItem[i].top);
		Window->draw(sItem[i]);
	}
}


void Inventory::drawMission(sf::RenderWindow* Window, sf::View* view) {
	//draw Mission
	sMission.setScale(0.7f, 0.7f);
	mBoxMission.left = view->getCenter().x - 300;
	mBoxMission.top = view->getCenter().y - 230;
	sMission.setPosition(mBoxMission.left, mBoxMission.top);

	Window->draw(sMission);

}

int Inventory::getCurrentMission(int x) {
	int mission = 0;
	if(x < 100 and x > 0)
		mission = 1;
	else if(x < 500 and x > 300)
		mission = 2;
	return mission;
}

std::string Inventory::getTextMission(int mission) {
	std::string textMission = "";
	if(mission == 0)
		textMission = "Mission: \nFind new mission\n";
	if(mission == 1)
		textMission = "Mission: \nFind another\n mission\n";
	if(mission == 2)
		textMission = "Mission: \nFind other mission\n";
	return textMission;
}
