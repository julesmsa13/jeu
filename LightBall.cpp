#include "LightBall.h"
#include <iostream>

LightBall::LightBall(const sf::Vector2f& position, const sf::Vector2f& dir, float spd, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    direction = dir;
    speed = spd;
}

bool LightBall::move(float deltaTime, Collision& collisionManager) {
    if (moveClock.getElapsedTime().asSeconds() > moveDelay) {
        sf::Vector2f movement = direction * speed * deltaTime;
        sprite.move(movement);

        sf::FloatRect ballRect(sprite.getPosition(), {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height});
        if (collisionManager.checkCollision(ballRect)) {
            return true; // Indicateur pour supprimer la flamme
        }
    }
    return false;
}

void LightBall::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}
