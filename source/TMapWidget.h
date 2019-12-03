#ifndef TMAPWIDGET_H
#define TMAPWIDGET_H

#include "SFML.hpp"


class TMapWidget {
	public:
		TMapWidget(int aX, int aY, int aWidth, int aHeight);	
		void Draw(sf::RenderWindow *Window);
		
	protected:
		int X, Y, Width, Height;
		sf::Texture texture;
};

#endif
