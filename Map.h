#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp> // Added SFML header for sf::Sprite

enum class TileType {
    Grass,
    Wall
};

class Map {
public:
    Map(int width, int height);
    TileType getTile(int x, int y) const;
    bool isWalkable(int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::vector<sf::Sprite> decoupeTileset(const std::string& filePath, int tileWidth, int tileHeight);

private:
    int width;
    int height;
    std::vector<std::vector<TileType>> grid;
};

#endif // MAP_H
