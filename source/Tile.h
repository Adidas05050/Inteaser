#ifndef TILE_H
#define TILE_H

#include "SFML.hpp"
#include "ctime"

namespace tinyxml2
{
	class XMLElement;
}

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

struct AnimationSprite
{
    AnimationSprite(sf::Sprite sprite, float duration) : TileSprite(sprite), Duration(duration) {}
    sf::Sprite TileSprite;
    float Duration = 0.f;
};

struct AnimationTiles
{
    AnimationTiles(std::vector<AnimationSprite> sprites) : TileSprite(std::move(sprites)) {}
    std::vector<AnimationSprite> TileSprite;

    mutable float ElapsedTime = 0;
    mutable int CurrentTile = 0;

};

struct TmxLayer
{
    sf::Uint8 opacity = 0;
    std::vector<AnimationTiles> tiles;
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

    void Draw();
    void Draw(int level);

private:
    sf::Clock   m_clock;
    float       m_prevTime;

	struct AnimationInfo
	{
		AnimationInfo(int frameId, float duration) : FrameId(frameId), Duration(duration) {}
		int     FrameId = 0;
		float   Duration = 0.f;
	};
    std::vector<AnimationInfo>    LoadAnimation(tinyxml2::XMLElement* element) const;

    int     GetSubRect(int index);
    void    LoadImages(tinyxml2::XMLElement* map, const std::string& filepath);


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
        std::map<int, std::vector<AnimationInfo>> Animations; // Карта анимаций ключ - Id анимированого тайла. значение - список фреймов
    };

    
    int m_currentTileInfo = 0;
    std::vector<TileInfo> m_tileInfo;

    std::vector<TmxObject> m_objects;
    std::vector<TmxLayer> m_layers;
};

#endif
