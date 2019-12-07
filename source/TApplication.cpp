#include "TApplication.hpp"
#define nullptr NULL
sf::Texture tBackground;
TApplication::TApplication(): Window(nullptr) {
	tBackground.loadFromFile("media/background/map.png");
	setTiles(tiles, "map/map.map");
}

void TApplication::Init() 
{
	Window = new sf::RenderWindow(sf::VideoMode(LEVEL_WIDTH, LEVEL_HEIGHT), "Menu");
	player = new Player(100, 100, 200, 5);
}

void TApplication::Run() 
{
	int alpha = 255;
	bool isClick = false;
	sf::Font font;
	font.loadFromFile("font/Cartoonic.otf");
	sf::Text text("", font, 54);
	
	
	while (Window->isOpen()) {
		sf::Color color(0, 0 , 0, alpha);
		text.setColor(color);
		sf::Event event;
		
		
		while (Window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
            		Window->close();
            }
		}
		
		Window->clear(sf::Color::White);
		for(int i = 0; i < TOTAL_TILES; i++){
				tiles[i]->draw(Window);
		}
		player->draw(Window, 10, 10);
		
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			isClick = true;
		if(isClick and alpha > 0)
		{
			alpha--;
		}
		if(alpha > 0) {
			text.setString ("DEMO");
			text.setPosition (340, 190);
			Window->draw (text);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			player->move(0);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			player->move(1);
		else
			player->move(4);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			player->move(2);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			player->move(3);
		
		Window->display();
	}
}

void TApplication::End() 
{
    if (Window != nullptr) {
    	delete Window;
    	
    	Window = nullptr;
    }
}
