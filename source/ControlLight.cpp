#include "ControlLight.h"
#include "World.h"

World world;

ControlLight::ControlLight(Tile *level) {
	renderTexture.create(LevelWidth, LevelHeight);
	renderColorTexture.create(LevelWidth, LevelHeight);
	tLight.loadFromFile("media/background/light.png"); //можно поменять на light, lightRev, LightWh; Стандарт light
	tColorLight.loadFromFile("media/background/lightWh.png");//
	tLight.setSmooth(true);
	tDialog.loadFromFile("media/background/dialog.png");
	sDialog.setTexture(tDialog);
	mObjectLight = level->GetAllObjects("light");
	count = mObjectLight.size();
	mBoxLight = new sf::FloatRect [count];
	mBoxColorLight = new sf::FloatRect [count];//
	sLight = new sf::Sprite [count];
	sColorLight = new sf::Sprite [count];//
	for(int i = 0; i < count; i++) {
		mBoxLight[i].width = mObjectLight[i].rect.width;
		mBoxLight[i].height = mObjectLight[i].rect.height;
		sLight[i].setTexture(tLight);
		//sLight[i].scale(LevelWidth / sLight[i].getTexture()->getSize().x, LevelHeight / sLight[i].getTexture()->getSize().y);
		mBoxColorLight[i].width = mObjectLight[i].rect.width;//
		mBoxColorLight[i].height = mObjectLight[i].rect.height;//
		sColorLight[i].setTexture(tColorLight);//
	}
}
//-------------------------------------------------------
void ControlLight::dialog(int id, bool *draw)
{

}
//-------------------------------------------------------
void ControlLight::draw(sf::RenderWindow* Window, sf::FloatRect playerBox, sf::View* view, bool dialog) {

	world.OnFrame(Window, view);

	if(dialog) {
		sDialog.setScale(0.5f, 0.3f);
		mBoxDialog.left = view->getCenter().x - 240;
		mBoxDialog.top = view->getCenter().y + 50;
		sDialog.setPosition(mBoxDialog.left, mBoxDialog.top);
		sDialog.setColor(sf::Color(255, 255, 255, 150));
		Window->draw(sDialog);
	}

	renderTexture.clear(sf::Color(0, 0, 0, world.GetTime() * 10));
	renderColorTexture.clear(sf::Color(0, 0, 0, world.GetTime() * 10));
	for(int i = 0; i < count; i++) {
		mBoxLight[i].left = mObjectLight[i].rect.left;
		mBoxLight[i].top = mObjectLight[i].rect.top;
		mBoxColorLight[i].left = mObjectLight[i].rect.left;//
		mBoxColorLight[i].top = mObjectLight[i].rect.top;//
		sLight[i].setScale(2.f, 2.f);
		sColorLight[i].setScale(2.f, 2.f);//
		float alphaRed = 50, alphaTorch = 50, alphaLamp = 50; //Для стандарта ставить на 255
		sLight[i].setPosition( mBoxLight[i].left - 76, mBoxLight[i].top - 76);
		sColorLight[i].setPosition( mBoxColorLight[i].left - 76, mBoxColorLight[i].top - 76);
		if(mObjectLight[i].type == "torch") {
			sLight[i].setColor(sf::Color(222, 125, 55));
			sColorLight[i].setColor(sf::Color(222, 125, 55, alphaTorch));
		} else if (mObjectLight[i].type == "lamp") {
			sLight[i].setColor(sf::Color(140, 196, 209));
			sColorLight[i].setColor(sf::Color(140, 196, 209, alphaLamp));
		} else if (mObjectLight[i].type == "player") {
			sLight[i].setColor(sf::Color(222, 125, 55));
			sColorLight[i].setColor(sf::Color(10, 255, 10, alphaTorch));
			sLight[i].setPosition(playerBox.left - mBoxLight[i].width - playerBox.width *2, playerBox.top - mBoxLight[i].height - playerBox.height / 2);
			sColorLight[i].setPosition(playerBox.left - mBoxColorLight[i].width - playerBox.width *2, playerBox.top - mBoxColorLight[i].height - playerBox.height / 2);
		} else {
			sLight[i].setColor(sf::Color(255.f, 0.f, 0.f));
			sColorLight[i].setColor(sf::Color(255.f, 0.f, 0.f, alphaRed));
		}
		renderColorTexture.draw(sColorLight[i], sf::BlendAlpha);
		renderTexture.draw(sLight[i], sf::BlendMultiply); //sf::BlendAdd, sf::BlendAlpha, sf::BlendMultiply - стандарт, sf::BlendNone

	}
	
	renderTexture.display();
	renderColorTexture.display();
	sf::Sprite sprite;
	sprite.setTexture(renderColorTexture.getTexture());
	Window->draw(sprite);
	sprite.setTexture(renderTexture.getTexture());
	Window->draw(sprite);
}
//-------------------------------------------------------
