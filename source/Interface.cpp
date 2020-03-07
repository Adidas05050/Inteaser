#include "Interface.h"

Interface::Interface(Tile *level) {
	renderTexture.create(LEVEL_WIDTH, LEVEL_HEIGHT); 
	tLight.loadFromFile("media/background/light.png"); //можно поменять на light, lightRev, LightWh 
	tLight.setSmooth(true);								 //Стандарт light
	mObjectLight = level->GetAllObjects("light"); 
	count = mObjectLight.size();
	mBoxLight = new sf::FloatRect [count];
	sLight = new sf::Sprite [count];

	for(int i = 0; i < count; i++) {
		mBoxLight[i].width = mObjectLight[i].rect.width;
		mBoxLight[i].height = mObjectLight[i].rect.height;
		sLight[i].setTexture(tLight);
	}

}

void Interface::draw(sf::RenderWindow* Window, sf::FloatRect playerBox, sf::View* view) {

	renderTexture.clear(sf::Color(0, 0, 0, 100));
	for(int i = 0; i < count; i++) {
		mBoxLight[i].left = mObjectLight[i].rect.left;
		mBoxLight[i].top = mObjectLight[i].rect.top;
		sLight[i].setScale(2.f, 2.f);
		float alphaRed = 255, alphaTorch = 255, alphaLamp = 255; //Для стандарта ставить на 255
		sLight[i].setPosition( mBoxLight[i].left - 76, mBoxLight[i].top - 76);
		if(mObjectLight[i].type == "torch") {
			sLight[i].setColor(sf::Color(222, 125, 55, alphaTorch));
		} else if (mObjectLight[i].type == "lamp") {
			sLight[i].setColor(sf::Color(140, 196, 209, alphaLamp));
		} else {
			sLight[i].setColor(sf::Color(255.f, 0.f, 0.f, alphaRed));
		}
		renderTexture.draw(sLight[i], sf::BlendMultiply); //sf::BlendAdd, sf::BlendAlpha, sf::BlendMultiply - стандарт, sf::BlendNone
	}

	renderTexture.display();
	
	sf::Sprite sprite(renderTexture.getTexture());
	Window->draw(sprite);
}
