#include "TApplication.hpp"
#define nullptr NULL

TApplication::TApplication(): Window(nullptr), MapWidget (nullptr)
{}

void TApplication::Init() 
{
	Window = new sf::RenderWindow(sf::VideoMode(800, 500), "Menu");
	MapWidget = new TMapWidget(0, 0, 800, 500);	
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
		MapWidget->Draw(Window);
		player->draw(Window, 1, 1);
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
		Window->display();
	}
}

void TApplication::End() 
{
    if (Window != nullptr) {
    	delete Window;
    	
    	Window = nullptr;
    }
    if (MapWidget != nullptr) {
    	delete MapWidget;
    	
    	MapWidget = nullptr;
	}
}
