#include "TApplication.hpp"
#define nullptr NULL
sf::Texture tBackground;
TApplication::TApplication(): Window(nullptr) {
	tBackground.loadFromFile("media/background/map.png");
	setTiles(tiles, "map/map.map");
}

void TApplication::Init() {
	Window = new sf::RenderWindow(sf::VideoMode(LEVEL_WIDTH, LEVEL_HEIGHT), "Menu");
	player = new Player(200, 200, 200, 3);
	inventory = new Inventory(10, 10);
	heroView.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	miniMap.reset(sf::FloatRect(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT));
	font.loadFromFile("font/Cartoonic.otf");
	textMission.setString("");
	textMission.setFont(font);
	textMission.setCharacterSize(24);

}

void TApplication::Run() {

	int viewX = SCREEN_WIDTH / 2, viewY = SCREEN_HEIGHT / 2;
	while (Window->isOpen()) {
		sf::Color color(0, 0 , 0, 255);
		textMission.setColor(color);
		sf::Event event;
		Window->setFramerateLimit(30);
		Window->setVerticalSyncEnabled(true);

		Window->setView(heroView);
		miniMap.setViewport(sf::FloatRect(0.7f, 0.02f, 0.3f, 0.22f));


		if((player->getCenterX() - (SCREEN_WIDTH / 2) > 0 ) and (player->getCenterX() + (SCREEN_WIDTH / 2) < LEVEL_WIDTH ))
			viewX = player->getCenterX();
		if((player->getCenterY() - (SCREEN_HEIGHT / 2) > 0) and (player->getCenterY() + (SCREEN_HEIGHT / 2) < LEVEL_HEIGHT))
			viewY = player->getCenterY();
		heroView.setCenter(viewX, viewY);


		Window->clear(sf::Color::White);
		while (Window->pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				Window->close();
			}
		}

		for(int i = 0; i < TOTAL_TILES; i++) {
			if(tiles[i]->getBox().intersects(sf::IntRect(viewX - (SCREEN_WIDTH / 2) - 5, viewY - (SCREEN_HEIGHT / 2) - 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT + 10))) {
				Window->setView(heroView);
				tiles[i]->draw(Window);
			}
		}

		player->draw(Window, 3, 3);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
			setInventory();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player->move(2);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player->move(1);
		} else {
			player->move(5);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			player->move(3);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			player->move(4);

		//-----------MiniMap--------------
		Window->setView(miniMap);
		for(int i = 0; i < TOTAL_TILES; i++)
				tiles[i]->draw(Window);
		
		player->draw(Window, 3, 3);
		Window->setView(heroView);
		//--------------------------------
		Window->display();
	}
}

void TApplication::setInventory() {
	inventory->draw(Window, &heroView);
	int mission;
	mission = inventory->getCurrentMission(player->getX());
	std::string currentTask;
	currentTask = inventory->getTextMission(mission);
	textMission.setString("Health: " + std::to_string(player->getHealth()) + "\n\n\n" + currentTask);
	textMission.setPosition(inventory->getX()+10, inventory->getY()+10);
	Window->draw(textMission);
}

void TApplication::End() {
	if (Window != nullptr) {
		delete Window;

		Window = nullptr;
	}
}
