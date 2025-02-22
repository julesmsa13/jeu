#include <thread>
#include <iostream>
#include <chrono>
#include "Character.h"
#include "Coord.h"
#include "Enemy.h"
#include "Orientation.h"
#include "Classe.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "TilesetManager.h"
#include "Player.h"
#include "Collision.h"
#include "LightBall.h"

void Game::run() {
    Map map(20, 20);
    Collision collisionManager;

    std::vector<sf::Sprite> tiles = TilesetManager::decoupeTileset("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/desert_1_0_7.png", 32, 32);

    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/grass2.png")) {
        std::cerr << "Erreur de chargement de la texture grass2.png" << std::endl;
        return;
    }

    sf::Clock waterAnimationClock;
    bool useWaterTexture1 = true;

    sf::Texture waterTexture1, waterTexture2;
    if (!waterTexture1.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/water.png")) {
        std::cerr << "Erreur de chargement de la texture water.png" << std::endl;
    }
    if (!waterTexture2.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/water2.png")) {
        std::cerr << "Erreur de chargement de la texture water2.png" << std::endl;
    }

    sf::Texture bottomBorderTexture;
    if (!bottomBorderTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/bordure_bas.png")) {
        std::cerr << "Erreur de chargement de la texture bordure_bas.png" << std::endl;
        return;
    }

    sf::Texture bottomLeftBorderTexture;
    if (!bottomLeftBorderTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/bordure_bas_gauche.png")) {
        std::cerr << "Erreur de chargement de la texture bordure_bas_gauche.png" << std::endl;
        return;
    }

    sf::Texture topBorderTexture, leftBorderTexture, rightBorderTexture, topLeftCornerTexture, topRightCornerTexture, bottomRightCornerTexture;

    if (!topBorderTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/bordure_haut.png") ||
        !leftBorderTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/bordure_gauche.png") ||
        !rightBorderTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/bordure_droite.png") ||
        !topLeftCornerTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/bordure_haut_gauche.png") ||
        !topRightCornerTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/bordure_haut_droite.png") ||
        !bottomRightCornerTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/bordure_bas_droite.png")) {
        std::cerr << "Erreur de chargement des textures de bordure" << std::endl;
        return;
    }

    sf::Texture treeTexture;
    if (!treeTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/arbre.png")) {
        std::cerr << "Erreur de chargement de la texture arbre.png" << std::endl;
        return;
    }

    sf::Texture houseTexture;
    if (!houseTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/maison.png")) {
        std::cerr << "Erreur de chargement de la texture maison.png" << std::endl;
        return;
    }

    sf::Texture bushTexture, logTexture;
    if (!bushTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/buisson.png") ||
        !logTexture.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/rondin.png")) {
        std::cerr << "Erreur de chargement des textures de buisson ou rondin" << std::endl;
        return;
    }

    sf::Texture flameTexture;
    if (!flameTexture.loadFromFile("gfx/animobjet/flamme.png")) {
        std::cerr << "Erreur de chargement de la texture flamme.png" << std::endl;
    } else {
        std::cout << "La texture flamme.png a été chargée avec succès." << std::endl;
    }

    Player player(map.getWidth(), map.getHeight());
    player.coord.x = 100; 
    player.coord.y = 100;

    sf::RenderWindow window(sf::VideoMode(640, 640), "Mon Jeu");

    // Mettre à jour les zones de collision avec les dimensions réelles
    std::vector<std::pair<sf::Vector2i, sf::Texture*>> collisionObjects = {
        {{5, 5}, &treeTexture}, {{7, 8}, &treeTexture}, {{10, 12}, &treeTexture}, {{15, 3}, &treeTexture}, {{12, 14}, &treeTexture},
        {{2, 5}, &bushTexture}, {{6, 10}, &bushTexture}, {{9, 6}, &bushTexture}, {{14, 14}, &bushTexture}, {{3, 7}, &bushTexture},
        {{8, 3}, &bushTexture}, {{11, 5}, &bushTexture}, {{13, 9}, &bushTexture}, {{5, 13}, &bushTexture}, {{7, 15}, &bushTexture},
        {{4, 4}, &logTexture}, {{11, 11}, &logTexture}, {{13, 8}, &logTexture}, {{3, 12}, &logTexture},
        {{3, 3}, &houseTexture}
    };

    for (const auto& obj : collisionObjects) {
        const auto& pos = obj.first;
        const auto& texture = obj.second;
        float width = texture->getSize().x;
        float height = texture->getSize().y;
        float adjustedY = pos.y * 32;
        if (texture == &treeTexture) {
            // Conserver seulement 10% de la hauteur pour le tronc
            height *= 0.1f;
            adjustedY += texture->getSize().y * 0.9f; // Ajuster la position pour le tronc
        } else if (texture == &houseTexture) {
            // Enlever 30% de la hauteur en partant du haut
            height *= 0.7f;
            adjustedY += texture->getSize().y * 0.3f; // Ajuster la position pour la maison
        }
        sf::FloatRect hitbox(pos.x * 32, adjustedY, width, height);
        collisionManager.addCollisionObject(hitbox);
    }

    // Ajouter des hitbox pour les bords de la carte (eau)
    for (int x = 0; x < map.getWidth(); ++x) {
        collisionManager.addCollisionObject(sf::FloatRect(x * 32, 0, 32, 32)); // Première ligne
        collisionManager.addCollisionObject(sf::FloatRect(x * 32, (map.getHeight() - 1) * 32, 32, 32)); // Dernière ligne
    }
    for (int y = 0; y < map.getHeight(); ++y) {
        collisionManager.addCollisionObject(sf::FloatRect(0, y * 32, 32, 32)); // Première colonne
        collisionManager.addCollisionObject(sf::FloatRect((map.getWidth() - 1) * 32, y * 32, 32, 32)); // Dernière colonne
    }

    struct EnemyState {
        Enemy enemy;
        sf::Sprite enemySprite;
        int direction;
        sf::Clock directionClock;
    };

    sf::Texture enemyTexture1, enemyTexture2, enemyTextureLeft1;
    enemyTexture1.loadFromFile("gfx/animmechant/base.png");
    enemyTexture2.loadFromFile("gfx/animmechant/base2.png");
    enemyTextureLeft1.loadFromFile("gfx/animmechant/basegauche.png");

    std::vector<EnemyState> enemies;
    for (int i = 0; i < 2; ++i) {
        float x, y;
        sf::FloatRect enemyRect;
        do {
            x = static_cast<float>(rand() % (map.getWidth() * 32));
            y = static_cast<float>(rand() % (map.getHeight() * 32));
            enemyRect = sf::FloatRect(x, y, 32, 32);
        } while (collisionManager.checkCollision(enemyRect));
        Coord position(x, y);
        Enemy enemy(Classe::Guerrier, 100, position, 1);
        EnemyState enemyState = { enemy, sf::Sprite(), rand() % 4, sf::Clock() };
        enemyState.enemySprite.setTexture(enemyTexture1);
        enemyState.enemySprite.setScale(32.f / enemyTexture1.getSize().x, 32.f / enemyTexture1.getSize().y);
        enemyState.enemySprite.setPosition(x, y);
        enemies.push_back(enemyState);
    }

    sf::Clock enemyMovementClock;
    sf::Time enemyMovementDelay = sf::seconds(0.01);

    float enemySpeed = 1.0f; // Vitesse de déplacement en pixels

    sf::Texture playerTexture1, playerTexture2, playerTextureLeft1, playerTextureLeft2;
    if (!playerTexture1.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/animjoueur/base.png") ||
        !playerTexture2.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/animjoueur/base2.png") ||
        !playerTextureLeft1.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/animjoueur/basegauche.png") ||
        !playerTextureLeft2.loadFromFile("C:/Users/Utilisateur/Desktop/M2/C++/Rendu/Jeu_Rendu_MASSA_Jules/Jeu_MASSA_Jules_Rendu/gfx/animjoueur/basegauche2.png")) {
        std::cerr << "Erreur de chargement de la texture base.png" << std::endl;
    }

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture1);

    // Assurez-vous que la taille du sprite correspond à la taille attendue pour les collisions
    playerSprite.setScale(32.f / playerTexture1.getSize().x, 32.f / playerTexture1.getSize().y);

    // Vérifier la position initiale pour éviter les zones de collision
    sf::FloatRect initialPlayerRect(player.coord.x, player.coord.y, 32, 32);
    if (collisionManager.checkCollision(initialPlayerRect)) {
        player.coord.x = 100; // Déplacer à une position sûre
        player.coord.y = 100;
    }

    // Mettre à jour la position du sprite du joueur
    playerSprite.setPosition(player.coord.x, player.coord.y);

    float playerSpeed = 5.0f; // Exemple de vitesse

    sf::Clock clock;
    sf::Clock inputClock;
    float inputDelay = 0.01f; // Délai de 200 ms entre les inputs

    int playerDirection = 0;
    sf::Clock playerDirectionClock;

    sf::Clock animationClock;
    float animationDelay = 0.5f; // Délai de 500 ms pour alterner les sprites

    sf::Clock enemyAnimationClock;
    float enemyAnimationDelay = 0.5f; // Délai de 500 ms pour alterner les sprites

    std::vector<LightBall> lightBalls;
    sf::Clock lightBallClock;
    float lightBallInterval = 6.0f; // Tirer toutes les 6 secondes

    while (window.isOpen()) {
        if (lightBallClock.getElapsedTime().asSeconds() > lightBallInterval) {
            for (const auto& enemyState : enemies) {
                // Créer des boules lumineuses dans les quatre directions
                std::vector<sf::Vector2f> directions = {
                    {1.f, 0.f}, {-1.f, 0.f}, {0.f, 1.f}, {0.f, -1.f}
                };
                for (const auto& dir : directions) {
                    sf::Vector2f position(enemyState.enemy.coord.x, enemyState.enemy.coord.y);
                    LightBall ball(position, dir, 40.f, flameTexture); // Passer la texture flamme.png
                    std::cout << "Création de la flamme à la position: " << position.x << ", " << position.y << std::endl;
                    lightBalls.push_back(ball);
                }
            }
            lightBallClock.restart();
        }

        // Déplacer les boules lumineuses et supprimer celles qui doivent être supprimées
        lightBalls.erase(std::remove_if(lightBalls.begin(), lightBalls.end(),
            [&collisionManager, deltaTime = clock.restart().asSeconds()](LightBall& ball) {
                return ball.move(deltaTime, collisionManager);
            }), lightBalls.end());

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Basculer l'affichage des zones de collision avec la touche 'e'
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            collisionManager.toggleDisplay();
            sf::sleep(sf::milliseconds(200)); // Attendre un moment pour éviter le basculement rapide
        }

        // Alterner entre les textures d'eau pour l'animation
        if (waterAnimationClock.getElapsedTime() > sf::seconds(1)) {
            useWaterTexture1 = !useWaterTexture1;
            waterAnimationClock.restart();
        }

        // Déplacer les ennemis aléatoirement avec un délai
        if (enemyMovementClock.getElapsedTime() > enemyMovementDelay) {
            for (auto& enemyState : enemies) {
                if (enemyState.directionClock.getElapsedTime() > sf::seconds(3)) {
                    enemyState.direction = rand() % 4;
                    enemyState.directionClock.restart();
                }
                sf::FloatRect enemyRect(enemyState.enemy.coord.x, enemyState.enemy.coord.y, 32, 32);
                switch (enemyState.direction) {
                    case 0: enemyRect.left -= enemySpeed; break; // Gauche
                    case 1: enemyRect.left += enemySpeed; break;  // Droite
                    case 2: enemyRect.top -= enemySpeed; break; // Haut
                    case 3: enemyRect.top += enemySpeed; break;  // Bas
                }
                if (!collisionManager.checkCollision(enemyRect)) {
                    switch (enemyState.direction) {
                        case 0: enemyState.enemy.coord.x -= enemySpeed; break; // Gauche
                        case 1: enemyState.enemy.coord.x += enemySpeed; break;  // Droite
                        case 2: enemyState.enemy.coord.y -= enemySpeed; break; // Haut
                        case 3: enemyState.enemy.coord.y += enemySpeed; break;  // Bas
                    }
                    enemyState.enemySprite.setPosition(enemyState.enemy.coord.x, enemyState.enemy.coord.y);
                }
            }
            enemyMovementClock.restart();
        }

        if (animationClock.getElapsedTime().asSeconds() > animationDelay) {
            if (playerDirection == 0) { // Gauche
                if (playerSprite.getTexture() == &playerTextureLeft1) {
                    playerSprite.setTexture(playerTextureLeft2);
                } else {
                    playerSprite.setTexture(playerTextureLeft1);
                }
            } else { // Droite ou autre
                if (playerSprite.getTexture() == &playerTexture1) {
                    playerSprite.setTexture(playerTexture2);
                } else {
                    playerSprite.setTexture(playerTexture1);
                }
            }
            animationClock.restart();
        }

        if (enemyAnimationClock.getElapsedTime().asSeconds() > enemyAnimationDelay) {
            for (auto& enemyState : enemies) {
                if (enemyState.direction == 0) { // Gauche
                    enemyState.enemySprite.setTexture(enemyTextureLeft1);
                } else { // Droite ou autre
                    if (enemyState.enemySprite.getTexture() == &enemyTexture1) {
                        enemyState.enemySprite.setTexture(enemyTexture2);
                    } else {
                        enemyState.enemySprite.setTexture(enemyTexture1);
                    }
                }
            }
            enemyAnimationClock.restart();
        }

        if (inputClock.getElapsedTime().asSeconds() > inputDelay) {
            // Gérer les entrées et les collisions
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerDirection = 0;
                playerSprite.setTexture(playerTextureLeft1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerDirection = 1;
                playerSprite.setTexture(playerTexture1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                playerDirection = 2;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                playerDirection = 3;
            }

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                playerDirection = -1; // Arrêter le mouvement
            }

            sf::FloatRect playerRect(player.coord.x, player.coord.y, 32, 32);
            switch (playerDirection) {
                case 0: playerRect.left -= playerSpeed; break; // Gauche
                case 1: playerRect.left += playerSpeed; break;  // Droite
                case 2: playerRect.top -= playerSpeed; break; // Haut
                case 3: playerRect.top += playerSpeed; break;  // Bas
                case -1: break; // Aucun mouvement
            }
            if (!collisionManager.checkCollision(playerRect)) {
                switch (playerDirection) {
                    case 0: player.coord.x -= playerSpeed; break; // Gauche
                    case 1: player.coord.x += playerSpeed; break;  // Droite
                    case 2: player.coord.y -= playerSpeed; break; // Haut
                    case 3: player.coord.y += playerSpeed; break;  // Bas
                }
            }

            // Mettre à jour la position du sprite du joueur
            playerSprite.setPosition(player.coord.x, player.coord.y);

            inputClock.restart();
        }

        window.clear(sf::Color(50, 50, 50)); // Gris foncé

        for (int y = 0; y < map.getHeight(); ++y) {
            for (int x = 0; x < map.getWidth(); ++x) {
                sf::RectangleShape tile(sf::Vector2f(32, 32));
                tile.setPosition(x * 32, y * 32);

                if (x == 0 || y == 0 || x == map.getWidth() - 1 || y == map.getHeight() - 1) {
                    tile.setTexture(useWaterTexture1 ? &waterTexture1 : &waterTexture2);
                } else if (x == 1 && y == 1) {
                    tile.setTexture(&topLeftCornerTexture);
                } else if (x == map.getWidth() - 2 && y == 1) {
                    tile.setTexture(&topRightCornerTexture);
                } else if (x == 1 && y == map.getHeight() - 2) {
                    tile.setTexture(&bottomLeftBorderTexture);
                } else if (x == map.getWidth() - 2 && y == map.getHeight() - 2) {
                    tile.setTexture(&bottomRightCornerTexture);
                } else if (y == 1) {
                    tile.setTexture(&topBorderTexture);
                } else if (x == 1) {
                    tile.setTexture(&leftBorderTexture);
                } else if (x == map.getWidth() - 2) {
                    tile.setTexture(&rightBorderTexture);
                } else if (y == map.getHeight() - 2) {
                    tile.setTexture(&bottomBorderTexture);
                } else {
                    tile.setTexture(&grassTexture);
                }

                window.draw(tile);
            }
        }

        // Dessiner les boules lumineuses après les tiles d'herbe
        for (const auto& ball : lightBalls) {
            ball.draw(window);
        }

        std::vector<sf::Vector2i> treePositions = {{5, 5}, {7, 8}, {10, 12}, {15, 3}, {12, 14}};
        std::vector<sf::Vector2i> bushPositions = {{2, 5}, {6, 10}, {9, 6}, {14, 14}, {3, 7}, {8, 3}, {11, 5}, {13, 9}, {5, 13}, {7, 15}};
        std::vector<sf::Vector2i> logPositions = {{4, 4}, {11, 11}, {13, 8}, {3, 12}};

        window.draw(playerSprite);

        // Dessiner les ennemis en jaune
        for (const auto& enemyState : enemies) {
            window.draw(enemyState.enemySprite);
        }

        for (const auto& pos : bushPositions) {
            sf::Sprite bushSprite;
            bushSprite.setTexture(bushTexture);
            bushSprite.setPosition(pos.x * 32, pos.y * 32);
            window.draw(bushSprite);
        }

        for (const auto& pos : logPositions) {
            sf::Sprite logSprite;
            logSprite.setTexture(logTexture);
            logSprite.setPosition(pos.x * 32, pos.y * 32);
            window.draw(logSprite);
        }

        for (const auto& pos : treePositions) {
            sf::Sprite treeSprite;
            treeSprite.setTexture(treeTexture);
            treeSprite.setPosition(pos.x * 32, pos.y * 32);
            window.draw(treeSprite);
        }

        sf::Sprite houseSprite;
        houseSprite.setTexture(houseTexture);
        houseSprite.setPosition(3 * 32, 3 * 32); 
        window.draw(houseSprite);

        collisionManager.draw(window); // Dessiner les zones de collision

        window.display();
    }
}
