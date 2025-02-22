#include "Collision.h"

Collision::Collision() : displayCollisions(false) {}

void Collision::addCollisionObject(const sf::FloatRect& rect) {
    collisionObjects.push_back(rect);
}

bool Collision::checkCollision(const sf::FloatRect& playerRect) const {
    for (const auto& object : collisionObjects) {
        if (object.intersects(playerRect)) {
            return true;
        }
    }
    return false;
}

void Collision::toggleDisplay() {
    displayCollisions = !displayCollisions;
}

void Collision::draw(sf::RenderWindow& window) const {
    if (displayCollisions) {
        for (const auto& object : collisionObjects) {
            sf::RectangleShape rect(sf::Vector2f(object.width, object.height));
            rect.setPosition(object.left, object.top);
            rect.setFillColor(sf::Color(0, 0, 255, 100)); // Bleu transparent
            window.draw(rect);
        }
    }
}
