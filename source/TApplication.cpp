#include "TApplication.hpp"
TApplication::TApplication(): Window(nullptr) {
	sf::Image img;
	img.loadFromFile("media/background/map.png");
	sf::Texture tBackground;
	tBackground.loadFromImage(img);
}

void TApplication::Init() {
	Window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Menu");
	inventory = new Inventory();
	level = new Tile();
	level->LoadFromFile("map/testMap.tmx");
	player = new Player(200, 200, 200, 10, level, Window);
	skelet = new Skelet(0, 10, level);
	interface = new Interface(level);
	heroView.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	miniMap.reset(sf::FloatRect(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT));
	font.loadFromFile("font/Cartoonic.otf");
	textMission.setString("");
	textMission.setFont(font);
	textMission.setCharacterSize(24);
	musicControl = new Music();
	Interaction = new Interactions();
	player->loadSound();
	musicControl->loadMusic("sounds/music/theme.wav");

}

void TApplication::Run() {
	float viewX = SCREEN_WIDTH / 2, viewY = SCREEN_HEIGHT / 2;
	bool dialog = false, drawDialog = false;
	int dialogID = 0;
	while (Window->isOpen()) {


		sf::Color color(0, 0 , 0, 255);
		textMission.setFillColor(color);
		sf::Event event;
		Window->setFramerateLimit(30);
		Window->setVerticalSyncEnabled(true);

		Window->setView(heroView);
		miniMap.setViewport(sf::FloatRect(0.7f, 0.02f, 0.3f, 0.22f));


		if((player->getCenterX() - (SCREEN_WIDTH / 2) > 0 ) and (player->getCenterX() + (SCREEN_WIDTH / 2) < LEVEL_WIDTH )) {
			if(player->getCenterX() - viewX > 0) {
				viewX += ((player->getCenterX() - viewX) / (SCREEN_HEIGHT / 12)) * player->mSpeed;
			} else {
				viewX -= ((viewX - player->getCenterX()) / (SCREEN_HEIGHT / 12)) * player->mSpeed;
			}
		}

		if((player->getCenterY() - (SCREEN_HEIGHT / 2) > 0) and (player->getCenterY() + (SCREEN_HEIGHT / 2) < LEVEL_HEIGHT)) {
			if(player->getCenterY() - viewY > 0) {
				viewY += ((player->getCenterY() - viewY) / (SCREEN_HEIGHT / 12)) * player->mSpeed;
			} else {
				viewY -= ((viewY - player->getCenterY()) / (SCREEN_HEIGHT / 12)) * player->mSpeed;
			}
		}


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
		if(!musicControl->mainMusic.getStatus()) {
			musicControl->mainMusic.setVolume(5.f);
				musicControl->mainMusic.play();//MUSIC
		}

		if(!dialog) {
			player->collisionSound();
			player->move();
			player->collision(skelet->getRect());
			
		}

		inventory->counterItem(Interaction->Interact(player, level));// Calculation interactable objects and give ID for inventory
		if(inventory->checkInventory(2, 3) and !skelet->alive()) {
			skelet->spawn(1100, 1100, 100);
			dialog = true;
			dialogID = 1;
		}
		player->draw(Window, 3, 3);
		skelet->draw(Window, 0.1, 0.1);
		inventory->drawInventory(Window, &heroView);
		interface->draw(Window, player->getRect(), &heroView, dialog);
		if(dialog) {
			interface->dialog(dialogID, &drawDialog);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				dialog = false;
				drawDialog = false;
			}
			
			Window->draw(interface->textForDraw);
			Window->draw(interface->textPlayer[0]);
		}
		
		if(!dialog) {
			Window->draw(Interaction->item);// for test
			Window->draw(Interaction->circ);// for test
			Window->draw(Interaction->recta);// for test
			Window->draw(Interaction->textForInteractibleObject);
		}
		player->OnFrame(Window, &heroView);
		Window->display();
	}
}
//----------------------------------?????????????WTF?????????????????--------------------------
void TApplication::setInventory() {
	inventory->drawMission(Window, &heroView);
	int mission;
	mission = inventory->getCurrentMission(player->getRect().left);
	std::string currentTask;
	currentTask = inventory->getTextMission(mission);
	textMission.setString("Health: " + std::to_string(player->getHealth()) + "\n\n\n" + currentTask);
	textMission.setPosition(heroView.getCenter().x - 250, heroView.getCenter().y - 220);
	Window->draw(textMission);
}
//----------------------------------------------------------------------------------------------
void TApplication::End() {
	if (Window != nullptr) {
		delete Window;

		Window = nullptr;
	}
}
