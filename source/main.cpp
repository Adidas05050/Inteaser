#include "TApplication.hpp"

sf::IntRect gTileClips[TILE_END];

int main(int argc, char *argv[])
{
   TApplication Application;
   Application.Init();
   Application.Run();
   Application.End();
 
   return 0;
}
