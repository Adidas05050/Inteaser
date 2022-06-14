#include "Inventory.h"

Inventory::Inventory(Entity* player)  :player(player)
{
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
	for (int i = 0; i < MAX_ITEM; i++)
		itemInventory[i] = -1;
	tApple.loadFromFile("media/item/apple.png");

}

int Inventory::checkInventory(int id, int count) {
	int needItem = 0;
	for(int i = 0; i < MAX_ITEM; i++) {
		if(itemInventory[i] == id)
			needItem++;
	}
	
	return (needItem >= count? true: false);
}
void Inventory::counterItem(int id)
{
	if(id == -1)
		return;
	int empty = -1;
	for(int i = 0; i < MAX_ITEM; i++)
		if(itemInventory[i] == -1)
		{
			empty = i;
			break;
		}

	if (empty == -1)
		return;

	auto it = itemMap.find(id);
	if(it !=itemMap.end()) {
		tItem[empty].loadFromFile("media/item/" + it->second + ".png");
		std::cout << it->second << '\n';
	} else {
		std::cout << "Item ID not found: " << id << std::endl;
	}
	sItem[empty].setTexture(tItem[empty]);
	sItem[empty].setScale(0.5f, 0.5f);
	itemInventory[empty] = id;
	UpdateItem();
}
void Inventory::UpdateItem()
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		sf::Sprite sprite;
		if (itemInventory[i] == -1)
		{
			tItem[i] = sf::Texture();
		}
		else
		{
			tItem[i] = tApple;
		}

		sprite.setTexture(tItem[i]);
		sprite.setScale(0.5f, 0.5f);
		sItem[i] = sprite;
	}

}

void Inventory::drawInventory(sf::RenderWindow* Window, sf::View* view)
{
	SetCurrentItem();
	UseItem();
	//draw Inventory
	sInventory.setScale(0.7f, 0.7f);
	mBoxInventory.left = view->getCenter().x + 120;
	mBoxInventory.top = view->getCenter().y - 280;
	sInventory.setPosition(mBoxInventory.left, mBoxInventory.top);

	Window->draw(sInventory);
	for(int i = 0; i < MAX_ITEM; i++) {
		mBoxItem[i].left = mBoxInventory.left + 19.5f * i;
		mBoxItem[i].top = mBoxInventory.top + mBoxInventory.height - 28;
		sItem[i].setPosition(mBoxItem[i].left, mBoxItem[i].top);
		Window->draw(sItem[i]);
	}

	sf::RectangleShape recta;
	recta.setSize(sf::Vector2f(mBoxInventory.width / MAX_ITEM - 10.f, mBoxInventory.height -11.f));
	//recta.setOrigin(sf::Vector2f(mBoxInventory.left, mBoxInventory.top));
	recta.setOutlineThickness(-1);
	recta.setFillColor(sf::Color(255, 0, 0, 50));
	recta.setOutlineColor(sf::Color(0, 0, 0));
	recta.setPosition(sf::Vector2f(mBoxInventory.left + 19.5 * m_currentItem + 2.f, mBoxInventory.top+1.f));

	g_window->draw(recta);
}


void Inventory::drawMission(sf::RenderWindow* Window, sf::View* view)
{
	mBoxMission.left = view->getCenter().x - 100;
	mBoxMission.top = view->getCenter().y - 150;
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
	std::string textMission = "Kill them all and go to the portal";
	return textMission;
}

void Inventory::UseItem()
{
	if (player == nullptr)
		return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if (itemInventory[m_currentItem] == 0) // apple
			player->SetDamage(-10);

		itemInventory[m_currentItem] = -1;
		UpdateItem();
	}
}
void Inventory::SetCurrentItem()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		m_currentItem = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		m_currentItem = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		m_currentItem = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		m_currentItem = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		m_currentItem = 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		m_currentItem = 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		m_currentItem = 6;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		m_currentItem = 7;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		m_currentItem = 8;
}
