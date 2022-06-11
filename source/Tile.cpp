#include "Tile.h"

#include <iostream>
#include "tinyxml2.h"

using namespace tinyxml2;

// On Windows, backslash '\\' is directory separator in paths
// On UNIX paths separated with slash '/'.
#if defined(_WIN32)
const char DIR_SEPARATOR = '\\';
#else
const char DIR_SEPARATOR = '/';
#endif
//-------------------------------------------------------
// Returns parent directory of given path;
std::string GetParentDirectory(const std::string &filepath)
{
    const size_t slashPos = filepath.find_last_of('/');
    std::string parentDir;
    if (slashPos != std::string::npos)
    {
        parentDir = filepath.substr(0, slashPos);
    }
    return parentDir;
}
//-------------------------------------------------------
// Joins two path fragments, e.g. directory path and filename
std::string JoinPaths(const std::string &path, const std::string &subpath)
{
    if (path.empty())
    {
        return subpath;
    }
    if (subpath.empty())
    {
        return path;
    }

    return path + DIR_SEPARATOR + subpath;
}
//-------------------------------------------------------
// Parses hex-encoded RGB like "6d9fb9"
sf::Color ParseColor(const std::string &hexRGB)
{
    char *pEnd = nullptr;
    const long hexValue = strtol(hexRGB.c_str(), &pEnd, 16);
    if (*pEnd != '\0')
    {
        throw std::runtime_error(hexRGB + " is not valid hex-encoded RGB color");
    }

    const uint8_t red = uint8_t((hexValue >> 16) % 256);
    const uint8_t green = uint8_t((hexValue >> 8) % 256);
    const uint8_t blue = uint8_t(hexValue % 256);

    return sf::Color(red, green, blue);
}
//-------------------------------------------------------
float ParseFloat(const std::string &str)
{
    char *pEnd = nullptr;
    const float value = strtof(str.c_str(), &pEnd);
    if (*pEnd != '\0')
    {
        throw std::runtime_error("'" + str + "' is not a float number");
    }

    return value;
}
//-------------------------------------------------------
int TmxObject::GetPropertyInt(const std::string &propertyName)
{
    return std::stoi(properties[propertyName].c_str());
}
//-------------------------------------------------------
float TmxObject::GetPropertyFloat(const std::string &propertyName)
{
    return ParseFloat(properties[propertyName].c_str());
}
//-------------------------------------------------------
std::string TmxObject::GetPropertyString(const std::string &propertyName)
{
    return properties[propertyName];
}
//-------------------------------------------------------
void TmxObject::MoveBy(const sf::Vector2f &movement)
{
    rect.left += movement.x;
    rect.top += movement.y;
    sprite.move(movement);
}
//-------------------------------------------------------
void TmxObject::MoveTo(const sf::Vector2f &position)
{
    rect.left = position.x;
    rect.top = position.y;
    sprite.setPosition(position);
}
//-------------------------------------------------------
int Tile::GetSubRect(int index)
{
    if (index == -1)
        return -1;

    // У каждого тайл-изображения нумерация идёт с 0 в текстуре.
    // Здесь происходит выбор из какой текстуры будут взяты координаты
    for(int i = 0; i < m_tileInfo.size(); i++)
    {
        const int firstId = m_tileInfo[i].FirstID;
        const int size = m_tileInfo[i].Size;
        if (index >= firstId && index < firstId + size)
        {
            m_currentTileInfo = i;
            return index - m_tileInfo[i].FirstID;
        }

    }
    return -1;
}
//-------------------------------------------------------
std::vector<Tile::AnimationInfo> Tile::LoadAnimation(XMLElement* element) const
{
    std::vector<Tile::AnimationInfo> animations;
    for (XMLElement* frameElement = element->FirstChildElement("frame"); frameElement != nullptr; frameElement = frameElement->NextSiblingElement("frame"))
    {
        const int tileId = std::stoi(frameElement->Attribute("tileid"));
        const int duration = std::stoi(frameElement->Attribute("duration"));
        animations.emplace_back(tileId, duration);
    }
    return animations;
}
//-------------------------------------------------------
void Tile::LoadImages(XMLElement* map, const std::string& filepath)
{
    
    for(XMLElement* element = map->FirstChildElement("tileset"); element != nullptr; element = element->NextSiblingElement("tileset"))
    {
        // Retrieve tileset description and the first tile GID (Group Identifier).
        
        const int firstTileID = std::stoi(element->Attribute("firstgid"));
        const int tileWidth = std::stoi(element->Attribute("tilewidth"));
        const int tileHeight = std::stoi(element->Attribute("tileheight"));
        const int size = std::stoi(element->Attribute("tilecount"));

        // <image> contains tileset texture
        XMLElement* image = element->FirstChildElement("image");
        const std::string imageFilename = image->Attribute("source");
        const std::string imagePath = JoinPaths(GetParentDirectory(filepath), imageFilename);
        sf::Color matteColor = sf::Color(0, 0, 0, 0);
        if (image->Attribute("trans") != nullptr)
        {
            matteColor = ParseColor(image->Attribute("trans"));
        }

        sf::Image img;
        if (!img.loadFromFile(imagePath))
        {
            std::cout << "Failed to load tile sheet." << std::endl;
            continue;
        }

        // Set tileset matte color, used to composite transparent image on
        //  background filled with matte color.
        img.createMaskFromColor(matteColor);
        sf::Texture texture;
        // Load texture from file.
        texture.loadFromImage(img);
        // Keep texture sharp when resized.
        texture.setSmooth(false);

        // Retrieve amount of rows and columns in tileset.
        const int columns = texture.getSize().x / tileWidth;
        const int rows = texture.getSize().y / tileHeight;

        // Collect texture rects list.
        // Each texture rect is subimage in tileset image, i.e. single tile image.
        std::vector<sf::IntRect> subRects;
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < columns; x++)
            {
                sf::IntRect rect;
                rect.top = y * tileHeight;
                rect.height = tileHeight;
                rect.left = x * tileWidth;
                rect.width = tileWidth;
                subRects.push_back(rect);
            }
        }
        // Заполняем информацию о тайл изображении
        TileInfo tileInfo(tileWidth, tileHeight, firstTileID, size, texture, subRects);

        //  Заполнение анимаций тайла
        const auto& animationElement = element->FirstChildElement("tile");
        if (animationElement != nullptr)
        {
            const int parentTileId = std::stoi(animationElement->Attribute("id"));
            tileInfo.Animations[parentTileId] = LoadAnimation(animationElement->FirstChildElement("animation"));
        }

        m_tileInfo.emplace_back(tileInfo);
    }
}
//-------------------------------------------------------
bool Tile::LoadFromFile(const std::string& filepath)
{
    XMLDocument levelFile;

    // Load XML into in-memory XMLDocument.
    if (levelFile.LoadFile(filepath.c_str()) != XML_SUCCESS)
    {
        throw std::runtime_error("Loading level \"" + filepath + "\" failed.");
    }

    // Element <map> should be root in TMX format.
    XMLElement* map = levelFile.FirstChildElement("map");
    if (map == 0)
    {
        throw std::runtime_error("<map> element not found");
    }
    // Map element example:
    //   <map version="1.0" orientation="orthogonal"
    //    width="10" height="10" tilewidth="34" tileheight="34">
    m_width = std::stoi(map->Attribute("width"));
    m_height = std::stoi(map->Attribute("height"));
    m_tileWidth = std::stoi(map->Attribute("tilewidth"));
    m_tileHeight = std::stoi(map->Attribute("tileheight"));

    LoadImages(map, filepath);

    ////////////////////////////////////////////////////////////////////////////
    /// Parse tile layers
    ///
    XMLElement *layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        TmxLayer layer;

        // Copy transparency if it set in XML,
        //  or make layer opaque (255).
        if (layerElement->Attribute("opacity") != nullptr)
        {
            float opacity = ParseFloat(layerElement->Attribute("opacity"));
            layer.opacity = sf::Uint8(255 * opacity);
        }
        else
        {
            layer.opacity = 255;
        }

        // <data> contains multiple tiles description.
        XMLElement *layerDataElement = layerElement->FirstChildElement("data");
        if (layerDataElement == nullptr)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        // <tile> contains single tile description.
        XMLElement *tileElement = layerDataElement->FirstChildElement("tile");
        if (tileElement == nullptr)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;
        while (tileElement)
        {
            int tileGID = -1;
            if(tileElement->FindAttribute("gid"))
                tileGID = std::stoi(tileElement->Attribute("gid"));
            const int subRectToUse = GetSubRect(tileGID);

            // Figure out texture rect for each tile.
            if (subRectToUse >= 0)
            {
                std::vector<AnimationSprite> animTiles;

                if (m_tileInfo[m_currentTileInfo].Animations[subRectToUse].empty())
                {
                    sf::Sprite sprite;
                    sprite.setTexture(m_tileInfo[m_currentTileInfo].Texture);
                    sprite.setTextureRect(m_tileInfo[m_currentTileInfo].SubRects[subRectToUse]);
                    sprite.setPosition(static_cast<float>(x * m_tileInfo[m_currentTileInfo].Width), static_cast<float>(y * m_tileInfo[m_currentTileInfo].Height));
                    sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                    animTiles.emplace_back(sprite, -1.f);
                }
                else
                {
	                for(const auto& anim : m_tileInfo[m_currentTileInfo].Animations[subRectToUse])
	                {
                        sf::Sprite sprite;
                        sprite.setTexture(m_tileInfo[m_currentTileInfo].Texture);
                        sprite.setTextureRect(m_tileInfo[m_currentTileInfo].SubRects[anim.FrameId]);
                        sprite.setPosition(static_cast<float>(x * m_tileInfo[m_currentTileInfo].Width), static_cast<float>(y * m_tileInfo[m_currentTileInfo].Height));
                        sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                        animTiles.emplace_back(sprite, anim.Duration / 1000.f);
	                }
                }
                layer.tiles.emplace_back(animTiles);

            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= m_width)
            {
                x = 0;
                y++;
                if (y >= m_height)
                {
                    y = 0;
                }
            }
        }

        m_layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    ////////////////////////////////////////////////////////////////////////////
    /// Collecting objects list.
    ///

    // If there are object layers.
    if (map->FirstChildElement("objectgroup") != nullptr)
    {
        XMLElement *objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            // Enter into <object> node
            XMLElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement)
            {
                // Collecting object properties - type, name, position, etc.
                std::string objectType;
                if (objectElement->Attribute("type") != nullptr)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != nullptr)
                {
                    objectName = objectElement->Attribute("name");
                }
                float x = std::stof(objectElement->Attribute("x"));
                float y = std::stof(objectElement->Attribute("y"));
                float width = 0;
                float height = 0;

                sf::Sprite sprite;
                sprite.setTexture(m_tileInfo[m_currentTileInfo].Texture);
                sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != nullptr)
                {
                    width = std::stof(objectElement->Attribute("width"));
                    height = std::stof(objectElement->Attribute("height"));
                }
                else
                {
                    if (objectElement->FindAttribute("gid"))
                    {
                        const size_t index = std::stoi(objectElement->Attribute("gid"));
                        width = static_cast<float>(m_tileInfo[m_currentTileInfo].SubRects[index].width);
                        height = static_cast<float>(m_tileInfo[m_currentTileInfo].SubRects[index].height);
                        sprite.setTextureRect(m_tileInfo[m_currentTileInfo].SubRects[index]);
                        sprite.setOrigin(0, height);
                    }
                }

                // Define object
                TmxObject object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::FloatRect objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                // Read object properties
                XMLElement *properties = objectElement->FirstChildElement("properties");
                if (properties != nullptr)
                {
                    XMLElement *prop = properties->FirstChildElement("property");
                    if (prop != nullptr)
                    {
                        while (prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                // Add object to list
                m_objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}
//-------------------------------------------------------
TmxObject Tile::GetFirstObject(const std::string &name) const
{
    // Only first object with given name
    for (size_t i = 0; i < m_objects.size(); i++)
        if (m_objects[i].name == name)
            return m_objects[i];
    throw std::runtime_error("Object with name " + name + " was not found");
}
//-------------------------------------------------------
std::vector<TmxObject> Tile::GetAllObjects(const std::string &name) const
{
    // All objects with given name
    std::vector<TmxObject> vec;
    for (size_t i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i].name == name)
        {
            vec.push_back(m_objects[i]);
        }
    }

    return vec;
}
//-------------------------------------------------------
sf::Vector2i Tile::GetTileSize() const
{
    return sf::Vector2i(m_tileWidth, m_tileHeight);
}
//-------------------------------------------------------
float Tile::GetTilemapWidth() const
{
    return static_cast<float>(m_tileWidth * m_width);
}
//-------------------------------------------------------
float Tile::GetTilemapHeight() const
{
    return static_cast<float>(m_tileHeight * m_height);
}
//-------------------------------------------------------
sf::Vector2f Tile::GetTilemapSize() const
{
    return sf::Vector2f(GetTilemapWidth(), GetTilemapHeight());
}
//-------------------------------------------------------
void Tile::Draw()
{
	float time = m_clock.getElapsedTime().asSeconds();
    const sf::FloatRect viewportRect = g_window->getView().getViewport();

    // Draw all tiles (and don't draw objects)
    for (const auto &layer : m_layers)
    {

        for (const auto& tiles : layer.tiles)
        {
            tiles.ElapsedTime += time - m_prevTime;
            if (tiles.TileSprite[tiles.CurrentTile].Duration > 0.f && tiles.ElapsedTime > tiles.TileSprite[tiles.CurrentTile].Duration)
            {
                tiles.CurrentTile += 1;
                if (tiles.CurrentTile >= tiles.TileSprite.size())
                    tiles.CurrentTile = 0;
                tiles.ElapsedTime = 0;
            }

            if (viewportRect.intersects(tiles.TileSprite[tiles.CurrentTile].TileSprite.getLocalBounds()))
            {
                g_window->draw(tiles.TileSprite[tiles.CurrentTile].TileSprite);
            }
            
        }
    }
    m_prevTime = time;
}
