#include "Inventory.h"

Inventory::Inventory(int x, int y) {
	mBox.left = x;
	mBox.top = y;

	texture.loadFromFile("media/background/missionbg.jpg");
	mBox.width = texture.getSize().x;
	mBox.height = texture.getSize().y;
	sInventory.setTexture(texture);
}

void Inventory::draw(sf::RenderWindow* Window, sf::View* view) {

	sInventory.setScale(0.7f, 0.7f);
	mBox.left = view->getCenter().x - 200;
	mBox.top = view->getCenter().y - 200;
	sInventory.setPosition(mBox.left, mBox.top);

	Window->draw(sInventory);
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

int Inventory::getX() {
	return mBox.left;
}
int Inventory::getY() {
	return mBox.top;
}
