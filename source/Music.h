#ifndef MUSIC_H
#define MUSIC_H

#include "SFML.hpp"
#include "string"
#include "map"
#include "iostream"

class Music
{
	public:
		void loadSound();
		void loadMusic(std::string path);
		sf::Music mainMusic;
		std::map<int, std::string> tileMap = 
		{
			{0, "wood"},
			{1, "gravel"}
		};
		
	protected:
		std::map<int, std::string>::iterator it;
		int currentNumberSound;
		std::string previousNameSound;
		sf::Sound stepSound[5];
		sf::SoundBuffer mBuffer[5];
		
};

#endif
