#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Character.h"
#include "Collision.h"

class Player : public Character {
public:
    Player(int mapWidth, int mapHeight);
    void handleInput(const Collision& collisionManager);
    void update();
    void draw(sf::RenderWindow &window);
    float getWidth() const { return shape.getSize().x; }
    float getHeight() const { return shape.getSize().y; }
    float getPlayerWidth() const { return shape.getSize().x; }
    float getPlayerHeight() const { return shape.getSize().y; }

private:
    sf::RectangleShape shape;
    float speed;
    sf::Clock movementClock;
    sf::Time movementDelay = sf::milliseconds(50);
    int mapWidth;
    int mapHeight;
};

#endif // PLAYER_H
