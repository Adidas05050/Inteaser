#include "TApplication.hpp"

extern sf::IntRect gTileClips[];

bool setTiles( Tile* tiles[], std::string path ) {
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map( path );

	//If the map couldn't be loaded
	if( map.fail() ) {
		std::cout << "Unable to load map file!\n";
		tilesLoaded = false;
	} else {
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i ) {
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if( map.fail() ) {
				//Stop loading map
				std::cout << "Error loading map: Unexpected end of file!\n";
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TILE_END ) ) {
				tiles[ i ] = new Tile( x, y, tileType );
			}
			//If we don't recognize the tile type
			else {
				//Stop loading map
				std::cout << "Error loading map: Invalid tile type at " << i <<"! \n";
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;
			//	std::cout << x << " ";
			//If we've gone too far
			if( x >= LEVEL_WIDTH ) {
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
				std::cout << y << std::endl;
			}
		}

		//Clip the sprite sheet
		if( tilesLoaded ) {

			gTileClips[ TILE_WOOD ].left = 0;
			gTileClips[ TILE_WOOD ].top = 0;
			gTileClips[ TILE_WOOD ].width = 32;
			gTileClips[ TILE_WOOD ].height = 32;

			gTileClips[ TILE_STONE ].left = 32;
			gTileClips[ TILE_STONE ].top = 0;
			gTileClips[ TILE_STONE ].width = 32;
			gTileClips[ TILE_STONE ].height = 32;

			gTileClips[ TILE_DESERT ].left = 64;
			gTileClips[ TILE_DESERT ].top = 0;
			gTileClips[ TILE_DESERT ].width = 32;
			gTileClips[ TILE_DESERT ].height = 32;


		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}
