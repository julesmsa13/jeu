#ifndef LIGHTBALL_H
#define LIGHTBALL_H

#include <SFML/Graphics.hpp>
#include "Collision.h"

class LightBall {
public:
    
    sf::Sprite sprite;
    sf::Vector2f direction;
    float speed;
    sf::Clock moveClock;
    float moveDelay = 0.1f; // Délai de 500 ms avant de commencer à bouger

    LightBall(const sf::Vector2f& position, const sf::Vector2f& dir, float spd, const sf::Texture& texture);
    bool move(float deltaTime, Collision& collisionManager);
    void draw(sf::RenderWindow& window) const;
};

#endif // LIGHTBALL_H
