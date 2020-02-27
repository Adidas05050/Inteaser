#ifndef INTERFACE_H
#define INTERFACE_H

#include "SFML.hpp"
#include "Tile.h"
#include <vector>

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

class Interface {
	public:
		Interface(Tile *level);
		void draw(sf::RenderWindow* Window, sf::FloatRect playerBox, sf::View* view);

	protected:
		std::vector<TmxObject> mObjectLight;
		sf::RenderTexture renderTexture;
		sf::FloatRect *mBoxLight;
		sf::Texture tLight;
		sf::Sprite *sLight;
		int count; // сомнительная польза, пока чисто для удоства
};

#endif
