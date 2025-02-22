#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Classe.h"   // Utilisation de l'énumération Classe
#include "Coord.h"    // Utilisation de la classe Coord pour la position
#include "Character.h" // Pour interagir avec la classe Character

class Enemy {
public:
    Classe classe;  // Classe de l'ennemi (Guerrier, Mage, Archer)
    int hp;         // Points de vie de l'ennemi
    Coord coord;    // Position de l'ennemi sur la carte
    int level;      // Niveau de l'ennemi (pour ajuster sa puissance d'attaque)

    // Constructeur
    Enemy(Classe classe, int hp, Coord coord, int level);

    // Méthodes
    void takeDamage(int damage);   // Prendre des dégâts
    void attack(Character& target); // Attaquer un personnage
    void move(int dx, int dy);     // Se déplacer sur la carte

    // Fonction pour récupérer la puissance d'attaque en fonction de la classe
    int getAttackPower() const;
};

#endif
