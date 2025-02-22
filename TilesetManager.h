#ifndef TILESETMANAGER_H
#define TILESETMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class TilesetManager {
public:
    static std::vector<sf::Sprite> decoupeTileset(const std::string& filePath, int tileWidth, int tileHeight);

private:
    static sf::Texture tilesetTexture; // Garde la texture en mémoire
};

#endif // TILESETMANAGER_H
