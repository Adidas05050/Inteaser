#include "Music.h"

Music::Music() {
	it = tileMap.begin();
	for(int i = 0; it != tileMap.end(); i++, it++) {
		if(!mBuffer[i].loadFromFile("sounds/short/" + it->second + ".wav")) 
		{
			std::cout << "error load sound "<< it->second << std::endl;
		}
		stepSound[i].setBuffer(mBuffer[i]);
	}
}

void Music::loadMusic(std::string path) {
	mainMusic.openFromFile(path);
}
