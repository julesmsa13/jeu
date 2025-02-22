#include "Map.h"
#include <cstdlib> // Pour rand()
#include <ctime>
#include <SFML/Graphics.hpp> // Pour sf::Texture et sf::Sprite
#include <iostream>

Map::Map(int width, int height) : width(width), height(height) {
    grid.resize(height, std::vector<TileType>(width, TileType::Grass));
    
    srand(time(0)); // Initialiser le générateur de nombres aléatoires

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (rand() % 10 < 2) { // 20% de chance de placer un mur
                grid[y][x] = TileType::Wall;
            }
        }
    }
}

TileType Map::getTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return TileType::Grass; // Valeur par défaut pour éviter un crash
    }
    return grid[y][x];
}

bool Map::isWalkable(int x, int y) const {
    return true; // Permettre au joueur de se déplacer partout
}

std::vector<sf::Sprite> Map::decoupeTileset(const std::string& filePath, int tileWidth, int tileHeight) {
    sf::Texture tileset;
    if (!tileset.loadFromFile(filePath)) {
        std::cerr << "Erreur de chargement du tileset" << std::endl;
        return {};
    }

    std::vector<sf::Sprite> tiles;
    int tilesetWidth = tileset.getSize().x;
    int tilesetHeight = tileset.getSize().y;

    for (int y = 0; y < tilesetHeight / tileHeight; ++y) {
        for (int x = 0; x < tilesetWidth / tileWidth; ++x) {
            sf::Sprite tile;
            tile.setTexture(tileset);
            tile.setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
            tiles.push_back(tile);
        }
    }

    return tiles;
}
