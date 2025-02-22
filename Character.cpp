#include "Character.h"
#include <iostream>  // Pour l'affichage de débogage si nécessaire

// Constructeur
Character::Character(Classe classe, int hp, Coord coord, Orientation orientation, int level)
    : classe(classe), hp(hp), coord(coord), orientation(orientation), level(level) {}

// Getter pour la classe
Classe Character::getClasse() {
    return classe;
}

// Méthode pour recevoir des dégâts
void Character::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) {
        hp = 0;  // On évite que les HP deviennent négatifs
    }
    std::cout << "Le personnage a pris " << damage << " de dégâts. PV restants: " << hp << std::endl;
}

// Méthode de déplacement : mise à jour des coordonnées
void Character::move(int dx, int dy) {
    coord.x += dx;
    coord.y += dy;
    std::cout << "Le personnage se déplace de (" << dx << ", " << dy << "). Nouvelle position: (" << coord.x << ", " << coord.y << ")." << std::endl;
}

// Tourner vers la gauche
void Character::turnLeft() {
    orientation = static_cast<Orientation>((orientation - 1 + 4) % 4);  // Rotation sur 4 directions
    std::cout << "Le personnage tourne vers la gauche." << std::endl;
}

// Tourner vers la droite
void Character::turnRight() {
    orientation = static_cast<Orientation>((orientation + 1) % 4);  // Rotation sur 4 directions
    std::cout << "Le personnage tourne vers la droite." << std::endl;
}

// Tourner vers le haut
void Character::turnUp() {
    orientation = Up;
    std::cout << "Le personnage tourne vers le haut." << std::endl;
}

// Tourner vers le bas
void Character::turnDown() {
    orientation = Down;
    std::cout << "Le personnage tourne vers le bas." << std::endl;
}

// Méthode pour faire monter le niveau du personnage
void Character::levelUp() {
    level++;
    // Exemple d'augmentation de la puissance d'attaque (à adapter selon la classe du personnage)
    std::cout << "Le personnage a monté de niveau ! Nouveau niveau: " << level << std::endl;

    // Augmenter les points de vie ou d'attaque en fonction du niveau ou de la classe (selon la logique du jeu)
    hp += 10;  // Ajout de points de vie à chaque niveau (exemple simple)
    std::cout << "Les PV sont augmentés. Nouveau total: " << hp << std::endl;
}
