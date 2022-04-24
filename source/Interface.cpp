#include "Interface.h"
#include "World.h"

World world;

Interface::Interface(Tile *level) {
	renderTexture.create(LEVEL_WIDTH, LEVEL_HEIGHT);
	renderColorTexture.create(LEVEL_WIDTH, LEVEL_HEIGHT);
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
		mBoxColorLight[i].width = mObjectLight[i].rect.width;//
		mBoxColorLight[i].height = mObjectLight[i].rect.height;//
		sColorLight[i].setTexture(tColorLight);//
	}
}
//-------------------------------------------------------
void Interface::dialog(int id, bool *draw) {
	if (*draw)
		return;
	file.open("dialogs/skelet/1.txt");
	std::string line;
	std::getline(file, line);
	file.close();
	int n = atoi(line.c_str());
	int numberLine = 0;
	bool *flags = new bool [n];
	std::string *text = new std::string [n];
	for(int i = 0; i < n; n++) {
		std::getline(file, text[i]);
		flags[i] = false;
	}
	int currentLine = atoi(text[numberLine].c_str());
	int character = atoi(text[numberLine].c_str());
	int nextLine = atoi(text[numberLine].c_str());
	int intervalDown = atoi(text[numberLine].c_str());
	int howManyLine = atoi(text[numberLine].c_str());

	fontForDraw.loadFromFile("font/single_day.ttf"); //TODO
	for(int i = 0; i < MAX_LINE_IN_DIALOG; i++ ) {
		if(character == 1) {
			textForDraw.setFont(fontForDraw);
			textForDraw.setString(text[i]);
			textForDraw.setFillColor(sf::Color(235, 235, 235, 255));
			textForDraw.setCharacterSize(20);
			textForDraw.setPosition(mBoxDialog.left + 60, mBoxDialog.top + 40);
		}

		else if(character == 2) {
			textPlayer[i].setString("");
			textPlayer[i].setFont(fontForDraw);
			textPlayer[i].setFillColor(sf::Color(235, 235, 235, 255));
			textPlayer[i].setCharacterSize(20);
			textPlayer[i].setPosition(mBoxDialog.left + 60, mBoxDialog.top + 80);
		}

	}
	*draw = true;
}

void Interface::draw(sf::RenderWindow* Window, sf::FloatRect playerBox, sf::View* view, bool dialog) {
	world.OnFrame();

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
			sColorLight[i].setColor(sf::Color(222, 125, 55, alphaTorch));
			sLight[i].setPosition(playerBox.left - mBoxLight[i].width - playerBox.width, playerBox.top - mBoxLight[i].height - playerBox.height / 2);
			sColorLight[i].setPosition(playerBox.left - mBoxColorLight[i].width - playerBox.width, playerBox.top - mBoxColorLight[i].height - playerBox.height / 2);
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
	world.DrawRain(Window, view);
}
//-------------------------------------------------------
