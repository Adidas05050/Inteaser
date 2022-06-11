#include "TApplication.hpp"
TApplication::TApplication()
{
	sf::Image img;
	img.loadFromFile("media/background/map.png");
	sf::Image grass;
	img.loadFromFile("media/background/grass.png");
	sf::Texture tBackground;
	tBackground.loadFromImage(img);
	tBackground.loadFromImage(grass);
}
//-------------------------------------------------------
void TApplication::Init() 
{
	g_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Menu");
	g_window->setFramerateLimit(30);
	g_window->setVerticalSyncEnabled(true);

	inventory = new Inventory();
	level = new Tile();
	level->LoadFromFile("map/testMap.tmx");
	player = new Player(200, 200, 200, 10, level, g_window);
	skelet = new Skelet(100, 10, level);
	interface = new ControlLight(level);
	m_heroView.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	m_guiView.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	miniMap.reset(sf::FloatRect(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT));
	font.loadFromFile("font/Cartoonic.otf");
	textMission.setString("");
	textMission.setFont(font);
	textMission.setCharacterSize(24);
	musicControl = new Music();
	Interaction = new Interactions();
	musicControl->loadMusic("sounds/music/theme.wav");

	m_viewPosition = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_heroView.setCenter(m_viewPosition.x, m_viewPosition.y);
}
//-------------------------------------------------------
void TApplication::Run() 
{
	
	bool dialog = false, drawDialog = false;
	int dialogID = 0;

	sf::Color color(0, 0, 0, 255);
	textMission.setFillColor(color);
	sf::Event event{};
	skelet->spawn(1100, 1100, 100);

	while (g_window->isOpen()) 
	{

		miniMap.setViewport(sf::FloatRect(0.7f, 0.02f, 0.3f, 0.22f));

		GuiView();
		SmoothCamera();

		g_window->clear(sf::Color::White);

		while (g_window->pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				g_window->close();
			}
		}
		
		level->Draw();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
			setInventory();
		}
		if(musicControl->mainMusic.getStatus() != sf::SoundStream::Status::Stopped) 
		{
			musicControl->mainMusic.setVolume(5.f);
				//musicControl->mainMusic.play();//MUSIC
		}

		if(!dialog) {
			player->CollisionSound();
			player->Move(skelet);
			skelet->Move(player->GetCenter());
		}

		inventory->counterItem(Interaction->Interact(player, level));// Calculation interactable objects and give ID for inventory
		//if(inventory->checkInventory(2, 3) and !skelet->IsAlive()) {
		//	dialog = true;
		//	dialogID = 1;
		//}
		player->Draw(2, 2);
		skelet->draw(2, 2);
		inventory->drawInventory(g_window, &m_guiView);
		interface->draw(g_window, player->GetRect(), &m_guiView, dialog);
		if(dialog) {
			interface->dialog(dialogID, &drawDialog);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				dialog = false;
				drawDialog = false;
			}
			
			g_window->draw(interface->textForDraw);
			g_window->draw(interface->textPlayer[0]);
		}
		
		if(!dialog) {
			g_window->draw(Interaction->item);// for test
			g_window->draw(Interaction->circ);// for test
			g_window->draw(Interaction->recta);// for test
			g_window->draw(Interaction->textForInteractibleObject);
		}
		player->OnFrame(&m_guiView);
		skelet->OnFrame(&m_guiView);
		g_window->display();
	}
}
//----------------------------------?????????????WTF?????????????????--------------------------
void TApplication::setInventory() 
{
	inventory->drawMission(g_window, &m_guiView);
	int mission;
	mission = inventory->getCurrentMission(player->GetRect().left);
	std::string currentTask;
	currentTask = inventory->getTextMission(mission);
	textMission.setString("Health: " + std::to_string(player->GetHealth()) + "\n\n\n" + currentTask);
	textMission.setPosition(m_guiView.getCenter().x - 250, m_guiView.getCenter().y - 220);
	g_window->draw(textMission);
}
//----------------------------------------------------------------------------------------------
void TApplication::End() 
{
	if (g_window == nullptr)
		return;

	delete g_window;
	g_window = nullptr;
	//TODO удалить ВСЕ указатели
}
//----------------------------------------------------------------------------------------------
void TApplication::SmoothCamera()
{
	g_window->setView(m_heroView);

	// Плавное движение камеры
	if ((player->GetCenter().x - (SCREEN_WIDTH / 2) > 0) and (player->GetCenter().x + (SCREEN_WIDTH / 2) < LEVEL_WIDTH)) {
		if (player->GetCenter().x - m_viewPosition.x > 0) {
			m_viewPosition.x += ((player->GetCenter().x - m_viewPosition.x) / (SCREEN_HEIGHT / 12)) * player->GetSpeed();
		}
		else {
			m_viewPosition.x -= ((m_viewPosition.x - player->GetCenter().x) / (SCREEN_HEIGHT / 12)) * player->GetSpeed();
		}
	}

	if ((player->GetCenter().y - (SCREEN_HEIGHT / 2) > 0) and (player->GetCenter().y + (SCREEN_HEIGHT / 2) < LEVEL_HEIGHT)) {
		if (player->GetCenter().y - m_viewPosition.y > 0) {
			m_viewPosition.y += ((player->GetCenter().y - m_viewPosition.y) / (SCREEN_HEIGHT / 12)) * player->GetSpeed();
		}
		else {
			m_viewPosition.y -= ((m_viewPosition.y - player->GetCenter().y) / (SCREEN_HEIGHT / 12)) * player->GetSpeed();
		}
	}

	m_heroView.setCenter(m_viewPosition);

}
//----------------------------------------------------------------------------------------------
void TApplication::GuiView()
{
	m_guiView.setCenter(m_viewPosition);
}
//----------------------------------------------------------------------------------------------


