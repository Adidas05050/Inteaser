#include "TMapWidget.h"


TMapWidget::TMapWidget(int aX, int aY, int aWidth, int aHeight): 
		X(aX), Y(aY), Width(aWidth), Height(aHeight)
{
	texture.loadFromFile("media/background/0.gif");
}

void TMapWidget::Draw(sf::RenderWindow *Window)
{
	sf::Sprite sBackground;
	sBackground.setTexture(texture);
	sBackground.setPosition(X, Y);
	float WidgetWidth = (float)Width/(float)texture.getSize().x;
	float WidgetHeight = (float)Height/(float)texture.getSize().y;
	sBackground.setScale(WidgetWidth, WidgetHeight);
	Window->draw(sBackground);
}
