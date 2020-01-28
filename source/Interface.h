#ifndef INTERFACE_H
#define INTERFACE_H

#include "SFML.hpp"
#include "Tile.h"
#include "iostream"

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

class Interface {
	public:
		Interface();
		void draw(sf::RenderWindow* Window, sf::FloatRect playerBox, sf::View* view);

	protected:
		sf::RenderTexture renderTexture;
		sf::FloatRect mBoxLight;
		sf::Texture tLight;
		sf::Sprite sLight;
		sf::Sprite sMouseLight;
};

#endif
