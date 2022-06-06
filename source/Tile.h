#ifndef TILE_H
#define TILE_H

#include "SFML.hpp"

namespace tinyxml2
{
	class XMLElement;
}

const int LEVEL_WIDTH = 3200;
const int LEVEL_HEIGHT = 3200;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct TmxObject
{
    int GetPropertyInt(const std::string &propertyName);
    float GetPropertyFloat(const std::string &propertyName);
    std::string GetPropertyString(const std::string &propertyName);

    void MoveBy(const sf::Vector2f &movement);
    void MoveTo(const sf::Vector2f &position);

    std::string name;
    std::string type;
    sf::FloatRect rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

struct TmxLayer
{
    sf::Uint8 opacity = 0;
    std::vector<sf::Sprite> tiles;
};

class Tile
{
  public:
    bool LoadFromFile(const std::string &filepath);

    TmxObject GetFirstObject(const std::string &name) const;
    std::vector<TmxObject> GetAllObjects(const std::string &name) const;
    sf::Vector2i GetTileSize() const;
    float GetTilemapWidth() const;
    float GetTilemapHeight() const;
    sf::Vector2f GetTilemapSize() const;

    void Draw() const;

  private:
    int GetSubRect(int index);
	void LoadImages(tinyxml2::XMLElement* map, const std::string& filepath);


    int m_width = 0;
    int m_height = 0;
    int m_tileWidth = 0;
    int m_tileHeight = 0;

    struct TileInfo
    {
        TileInfo(int width, int height, int firstId, int size, sf::Texture texture, std::vector<sf::IntRect> subRects)
	        : Width(width), Height(height), FirstID(firstId), Size(size), Texture(texture), SubRects(subRects)
    	{}
        int Width = 0;
        int Height = 0;
        int FirstID = 0;
        int Size = 0;
        sf::Texture Texture;
        std::vector<sf::IntRect> SubRects;
    };

    int m_currentTileInfo = 0;
    std::vector<TileInfo> m_tileInfo;

    std::vector<TmxObject> m_objects;
    std::vector<TmxLayer> m_layers;
};

#endif
