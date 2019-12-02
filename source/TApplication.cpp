#include "TApplication.hpp"


TApplication::TApplication(): Window(nullptr), MapWidget (nullptr)
{}

void TApplication::Init() 
{
	Window = new sf::RenderWindow(sf::VideoMode(800, 500), "Menu");
	MapWidget = new TMapWidget(0, 0, 800, 500);	
}

void TApplication::Run() 
{
	int frame = 0, tileGif = 0, menuNum = 0;
	sf::Font font;
	font.loadFromFile("font/Cartoonic.otf");
	sf::Text text("", font, 54);
	text.setColor(sf::Color::Black);
	while (Window->isOpen()) 
	{
		sf::Event event;
		while (Window->pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
            		Window->close();
		}
		
		Window->clear(sf::Color::White);
		
		MapWidget->Draw(Window);

		text.setString(L"DEMO");
		text.setPosition(340, 190);
		Window->draw(text);

		Window->display();
	}
}

void TApplication::End() 
{
    if (Window != nullptr)
    {
    	delete Window;
    	Window = nullptr;
    }
    if (MapWidget != nullptr)
    {
    	delete MapWidget;
    	MapWidget = nullptr;
	}
}
