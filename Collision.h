#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Collision {
public:
    Collision();
    void addCollisionObject(const sf::FloatRect& rect);
    bool checkCollision(const sf::FloatRect& playerRect) const;
    void toggleDisplay();
    void draw(sf::RenderWindow& window) const;

private:
    std::vector<sf::FloatRect> collisionObjects;
    bool displayCollisions = false;
};

#endif // COLLISION_H
