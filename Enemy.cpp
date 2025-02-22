#include <iostream>
#include "Enemy.h"
#include "Character.h" // Pour interagir avec la classe Character

// Constructeur de la classe Enemy
Enemy::Enemy(Classe classe, int hp, Coord coord, int level)
    : classe(classe), hp(hp), coord(coord), level(level) {}

// M�thode pour appliquer des d�g�ts � l'ennemi
void Enemy::takeDamage(int damage) {
    hp -= damage; // R�duit les points de vie de l'ennemi
    if (hp < 0) {
        hp = 0; // On ne peut pas avoir des points de vie n�gatifs
    }
}

// M�thode pour que l'ennemi attaque un personnage
void Enemy::attack(Character& target) {
    // On r�cup�re la puissance d'attaque de l'ennemi selon sa classe
    int damage = getAttackPower();
    target.takeDamage(damage); // Le personnage prend des d�g�ts
    std::cout << "Enemy attacks! Character takes " << damage << " damage." << std::endl;
}

// M�thode pour d�placer l'ennemi
void Enemy::move(int dx, int dy) {
    // On d�place l'ennemi selon les coordonn�es dx et dy
    coord.x += dx;
    coord.y += dy;
    std::cout << "Enemy moves to position (" << coord.x << ", " << coord.y << ")." << std::endl;
}

// Fonction qui renvoie la puissance d'attaque selon la classe de l'ennemi
int Enemy::getAttackPower() const {
    switch (classe) {
    case Guerrier:
        return 10;  // Exemple : Guerrier a une puissance d'attaque de 10
    case Mage:
        return 8;   // Mage a une puissance d'attaque de 8
    case Archer:
        return 6;   // Archer a une puissance d'attaque de 6
    default:
        return 0;   // Valeur par d�faut (au cas o�)
    }
}
