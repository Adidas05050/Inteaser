#include "Interface.h"

Interface::Interface() {
	renderTexture.create(LEVEL_WIDTH, LEVEL_HEIGHT);
	tLight.loadFromFile("media/background/light.png");
	mBoxLight.width = tLight.getSize().x;
	mBoxLight.height = tLight.getSize().y;
	tLight.setSmooth(true);
	sLight.setTexture(tLight);
	sMouseLight.setTexture(tLight);
}

void Interface::draw(sf::RenderWindow* Window, sf::FloatRect playerBox, sf::View* view) {
	sf::Vector2f mouse_world =  Window->mapPixelToCoords(sf::Mouse::getPosition( *Window ) );

	sMouseLight.setPosition(mouse_world);
	
	mBoxLight.left = playerBox.left;
	mBoxLight.top = playerBox.top;
	sLight.setScale(2.f, 2.f);
	
	//Слишком огромная, надо оптимизировать
	sLight.setPosition( mBoxLight.left - playerBox.width/2 + (mBoxLight.width / 2) - ((mBoxLight.width * sLight.getScale().x) / 2), //выравнивание по центру игрока по Х
						mBoxLight.top - playerBox.height/2 + (mBoxLight.height / 2) - ((mBoxLight.height * sLight.getScale().y) / 2) ); //выравнивание по центру игрока по У
	//---------------------------------------
	
	
	renderTexture.clear(sf::Color(0, 0, 0, 100));
	renderTexture.draw(sLight, sf::BlendMultiply);
	renderTexture.draw(sMouseLight, sf::BlendMultiply);
	renderTexture.display();
	
	
	
	sf::Sprite sprite(renderTexture.getTexture());
	//float luminosity = 200.0f;
  	//sprite.setColor(sf::Color(10.0f, 10.0f, 10.0f, luminosity));
	Window->draw(sprite);


}
