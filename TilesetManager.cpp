#include "TilesetManager.h"
#include <iostream>

sf::Texture TilesetManager::tilesetTexture; // Définit la texture statique

std::vector<sf::Sprite> TilesetManager::decoupeTileset(const std::string& filePath, int tileWidth, int tileHeight) {
    std::cout << "Tentative de chargement du fichier: " << filePath << std::endl;
    if (!tilesetTexture.loadFromFile(filePath)) {
        std::cerr << "Erreur de chargement du tileset: " << filePath << std::endl;
        return {};
    }

    std::vector<sf::Sprite> tiles;
    int tilesetWidth = tilesetTexture.getSize().x;
    int tilesetHeight = tilesetTexture.getSize().y;

    std::cout << "Taille du tileset: " << tilesetWidth << "x" << tilesetHeight << std::endl;

    if (tilesetWidth == 0 || tilesetHeight == 0) {
        std::cerr << "Erreur: Taille du tileset invalide." << std::endl;
        return {};
    }

    for (int y = 0; y < tilesetHeight / tileHeight; ++y) {
        for (int x = 0; x < tilesetWidth / tileWidth; ++x) {
            sf::Sprite tile;
            tile.setTexture(tilesetTexture);
            tile.setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
            tiles.push_back(tile);
        }
    }

    std::cout << "Nombre de tuiles découpées: " << tiles.size() << std::endl;

    return tiles;
}
