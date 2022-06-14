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

	levels.push_back(Tile());
	levels.push_back(Tile());
	levels.push_back(Tile());
	levels[0].LoadFromFile("map/level1.tmx");

	font.loadFromFile("font/Cartoonic.otf");
	textMission.setString("");
	textMission.setFont(font);
	textMission.setCharacterSize(24);
	Tips.setFillColor(sf::Color::White);
	Tips.setOutlineColor(sf::Color::White);
	Tips.setString("Controls: WASD\nPick UP: E\nInventory: 1-9\nUse inventory item: Q\nAttack: LBM.\nTeleport: L.Shift\nOpen: ~");
	Tips.setFont(font);
	Tips.setCharacterSize(26);

	musicControl = new Music();
	Interaction = new Interactions();
	musicControl->loadMusic("sounds/music/theme.wav");
}
//-------------------------------------------------------
void TApplication::StartLevel(int level)
{
	m_enemies.clear();
	levels[level] = Tile();
	levels[level].LoadFromFile("map/level" + std::to_string(level + 1) + ".tmx");
	// Положение игрока
	const sf::FloatRect playerRect = levels[m_currentLevel].GetFirstObject("player").rect;

	player = new Player(playerRect.left, playerRect.top, 200, 10, &levels[m_currentLevel], g_window);

	// Положение врагов
	const auto& enemies = levels[m_currentLevel].GetAllObjects("enemy");
	for (const auto enemy : enemies)
	{
		Skelet::Type type = Skelet::Type::Bandit;
		if (enemy.type == "ara")
			type = Skelet::Type::Ara;
		float health = type == Skelet::Type::Bandit ? 20: 5;
		float speed = type == Skelet::Type::Bandit ? 7: 12;
		Skelet* skelet = new Skelet(health, speed, &levels[m_currentLevel], type);
		skelet->spawn(player, enemy.rect.left, enemy.rect.top, 20);
		m_enemies.push_back(skelet);
		
	}
	enemiesInLevelRemained = m_enemies.size();

	LevelWidth = levels[m_currentLevel].GetTilemapWidth();
	LevelHeight = levels[m_currentLevel].GetTilemapHeight();
	interface = new ControlLight(&levels[m_currentLevel]);

	m_heroView.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	m_guiView.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	miniMap.reset(sf::FloatRect(0, 0, LevelWidth, LevelHeight));
	m_viewPosition = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	inventory = new Inventory(player);
}
//-------------------------------------------------------
void TApplication::Run() 
{

	StartLevel(m_currentLevel);
	bool dialog = false, drawDialog = false;
	int dialogID = 0;
	
	textMission.setFillColor(sf::Color::White);
	textMission.setOutlineColor(sf::Color::Black);
	textMission.setOutlineThickness(2.f);
	sf::Event event{};

	while (g_window->isOpen()) 
	{
		g_window->clear(sf::Color::White);

		// Подсчёт живых каждый кадр:\

		enemiesInLevelRemained = 0;
		for (const auto& enemy : m_enemies)
			enemiesInLevelRemained += enemy->IsAlive();

		if (enemiesInLevelRemained == 0 && m_isUsedPortal)
		{
			m_currentLevel++;
			if (m_currentLevel > 2)
				m_currentLevel = 0;
			StartLevel(m_currentLevel);
		}
		

		if(!player->IsAlive())
			StartLevel(m_currentLevel);

		miniMap.setViewport(sf::FloatRect(0.7f, 0.02f, 0.3f, 0.22f));

		GuiView();
		SmoothCamera();

		levels[m_currentLevel].Draw();

		while (g_window->pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				g_window->close();
			}
		}
		

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
			player->Move(m_enemies);
			for(const auto& enemy : m_enemies)
				enemy->Move(player->GetCenter());
		}

		inventory->counterItem(Interaction->Interact(player, &levels[m_currentLevel]));// Calculation interactable objects and give ID for inventory

		player->Draw(2, 2);
		for (const auto& enemy : m_enemies)
			enemy->draw(2, 2);
		
		interface->draw(g_window, player->GetRect(), &m_guiView, dialog);
		if(dialog) {
			interface->dialog(dialogID, &drawDialog);
			
			g_window->draw(interface->textForDraw);
			g_window->draw(interface->textPlayer[0]);
		}
		
		if(!dialog) {
			//g_window->draw(Interaction->item);// for test
			//g_window->draw(Interaction->circ);// for test
			//g_window->draw(Interaction->recta);// for test
			g_window->draw(Interaction->textForInteractibleObject);
		}
		player->OnFrame(&m_guiView);
		for (const auto& enemy : m_enemies)
			enemy->OnFrame(&m_guiView);

		CheckPortal();
		inventory->drawInventory(g_window, &m_guiView);

		const bool isPressedTilde = sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde);
		if (m_isShowTips || isPressedTilde)
		{
			if(isPressedTilde)
			m_isShowTips = false;
			Tips.setPosition(m_guiView.getCenter().x+100, m_guiView.getCenter().y - 220);
			g_window->draw(Tips);
		}

		g_window->display();
	}
}
//------------------------------------------------------------
void TApplication::CheckPortal()
{
	m_isUsedPortal = false;
	const sf::FloatRect portalRect = levels[m_currentLevel].GetFirstObject("portal").rect;
	if (player->GetRect().intersects(portalRect))
	{
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(16);

		if (enemiesInLevelRemained != 0)
		{
			text.setFillColor({ 100, 50, 50, 255 });
			text.setString("Finish the mission.\n(Press \"Tab\")");
		}
		else
		{
			text.setFillColor({ 150, 150, 150, 255 });
			text.setString("Use portal.\n(Press F)");
		}

		text.setPosition(portalRect.left + portalRect.width, portalRect.top - 20);
		g_window->draw(text);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			m_isUsedPortal = true;
	}
}
//------------------------------------------------------------
void TApplication::setInventory() 
{
	inventory->drawMission(g_window, &m_guiView);
	int mission;
	mission = inventory->getCurrentMission(player->GetRect().left);
	std::string currentTask;
	currentTask = inventory->getTextMission(mission);
	textMission.setString("Tip: " + currentTask + "\n\nRemained: " + std::to_string(enemiesInLevelRemained));
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
	if ((player->GetCenter().x - (SCREEN_WIDTH / 2) > 0) and (player->GetCenter().x + (SCREEN_WIDTH / 2) < LevelWidth)) {
		if (player->GetCenter().x - m_viewPosition.x > 0) {
			m_viewPosition.x += ((player->GetCenter().x - m_viewPosition.x) / (SCREEN_HEIGHT / 12)) * player->GetSpeed();
		}
		else {
			m_viewPosition.x -= ((m_viewPosition.x - player->GetCenter().x) / (SCREEN_HEIGHT / 12)) * player->GetSpeed();
		}
	}

	if ((player->GetCenter().y - (SCREEN_HEIGHT / 2) > 0) and (player->GetCenter().y + (SCREEN_HEIGHT / 2) < LevelHeight)) {
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


