#ifndef INTERFACE_H
#define INTERFACE_H

#include "SFML.hpp"
#include "Tile.h"
#include <vector>
#include <fstream>
#include <cstring>
#include <iostream> //DEBUG
const int MAX_LINE_IN_DIALOG = 5;
class ControlLight
{
public:
	ControlLight(Tile* level);
	void draw(sf::RenderWindow* Window, sf::FloatRect playerBox, sf::View* view, bool dialog);
	void dialog(int id, bool* draw);
	sf::Font fontForDraw;
	sf::Text textForDraw;
	sf::Text textPlayer[MAX_LINE_IN_DIALOG];

protected:
	std::ifstream file;
	std::vector<TmxObject> mObjectLight;
	sf::RenderTexture renderTexture;
	sf::RenderTexture renderColorTexture;
	sf::FloatRect* mBoxLight;
	sf::FloatRect* mBoxColorLight;
	sf::Texture tLight;
	sf::Texture tColorLight;
	sf::Sprite* sColorLight;
	sf::Sprite* sLight;
	sf::Sprite sDialog;
	sf::Texture tDialog;
	sf::FloatRect mBoxDialog;

	int count; // сомнительная польза, пока чисто для удоства
private:
	sf::RenderWindow* m_window = nullptr;
};

#endif
