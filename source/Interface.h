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
		sf::RenderTexture renderColorTexture;
		sf::FloatRect *mBoxLight;
		sf::FloatRect *mBoxColorLight;
		sf::Texture tLight;
		sf::Texture tColorLight;
		sf::Sprite *sColorLight;
		sf::Sprite *sLight;
		int count; // ������������ ������, ���� ����� ��� �������
};

#endif
