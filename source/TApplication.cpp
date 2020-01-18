#include "TApplication.hpp"
#define nullptr NULL
sf::Texture tBackground;
TApplication::TApplication(): Window(nullptr) {
	tBackground.loadFromFile("media/background/map.png");
}

void TApplication::Init() {
	Window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Menu");
	inventory = new Inventory(10, 10);
	level = new Tile();
	level->LoadFromFile("map/testMap.tmx");
	player = new Player(200, 200, 200, 10, level);
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
		textMission.setFillColor(color);
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

		level->Draw(*Window);



		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
			setInventory();
		}

		player->move();
		player->collision();
		player->draw(Window, 3, 3);
		Window->display();
	}
}

void TApplication::setInventory() {
	inventory->draw(Window, &heroView);
	int mission;
	mission = inventory->getCurrentMission(player->getRect().left);
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
