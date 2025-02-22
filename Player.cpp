#include <iostream>
#include "Player.h"

Player::Player(int mapWidth, int mapHeight) : Character(Classe::Guerrier, 100, Coord(10, 10), Orientation::Up, 1), speed(3.0f), mapWidth(mapWidth), mapHeight(mapHeight) {
    shape.setSize(sf::Vector2f(32, 32));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(coord.x * 32, coord.y * 32); // Position initiale
    movementClock.restart();
}

void Player::handleInput(const Collision& collisionManager) {
    if (movementClock.getElapsedTime() > movementDelay) {
        sf::FloatRect playerRect = shape.getGlobalBounds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerRect.left -= speed;
            if (!collisionManager.checkCollision(playerRect)) {
                shape.move(-speed, 0);
                coord.x -= 1;
                std::cout << "Position X: " << coord.x << std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerRect.left += speed;
            if (!collisionManager.checkCollision(playerRect)) {
                shape.move(speed, 0);
                coord.x += 1;
                std::cout << "Position X: " << coord.x << std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerRect.top -= speed;
            if (!collisionManager.checkCollision(playerRect)) {
                shape.move(0, -speed);
                coord.y -= 1;
                std::cout << "Position Y: " << coord.y << std::endl;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerRect.top += speed;
            if (!collisionManager.checkCollision(playerRect)) {
                shape.move(0, speed);
                coord.y += 1;
                std::cout << "Position Y: " << coord.y << std::endl;
            }
        }
        movementClock.restart();
    }
}

void Player::update() {
    // Mettre à jour la position ou d'autres états si nécessaire
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(shape);
}
