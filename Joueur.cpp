#include "Joueur.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include<string>


Joueur::Joueur(std::string clr) : couleur(clr), billets(10), position(0), nbstands(10) {
}

int Joueur::lancerDe() {
    int de = std::rand() % 6 + 1;
    avancer(de);
    return de;
}

void Joueur::payerStand(int montant) {
    billets -= montant;
}

void Joueur::acheterStand(int index, int prix) {
    if (nbstands == 0) {
        std::cout << "Pas de stands restants." << std::endl;
        return;
    }
    if (billets < prix) {
        std::cout << "Fonds insuffisants pour acheter le stand." << std::endl;
        return;
    }
    nbstands--;
    billets -= prix;
    standPlayer.push_back(index);
    std::cout << "Stand achete a la case " << index << "." << std::endl;
}

int Joueur::getBillets() const {
    return billets;
}

void Joueur::payerJoueur(int montant) {
    billets -= montant;
}

void Joueur::ajouterArgent(int montant) {
    billets += montant;
}

int Joueur::getPosition() {
    return position;
}

void Joueur::avancer(int nbCases) {
    position = (position + nbCases) % 31;
}

std::string Joueur::getCouleur() const {
    return couleur;
}
void Joueur::retirStand(int case1) {
    auto it = std::find(standPlayer.begin(), standPlayer.end(), case1);
    if (it != standPlayer.end()) {
        standPlayer.erase(it);
        nbstands++;
    }
}

bool Joueur::echangerStand(int case1) {
    std::sort(standPlayer.begin(), standPlayer.end());
    auto it = std::find(standPlayer.begin(), standPlayer.end(), case1);
    if (it == standPlayer.end()) return true; // Si le joueur ne possède pas déjà la case, autoriser

    int index = std::distance(standPlayer.begin(), it);

    // Vérifier les limites
    if (index + 1 < (int)standPlayer.size() && standPlayer[index + 1] == case1 + 1)
        return false;

    if (index - 1 >= 0 && standPlayer[index - 1] == case1 - 1)
        return false;

    return true;
}


void Joueur::stand_initialisation(int nbjoueur) {
    if (nbjoueur == 2) {
        nbstands = 15;
    }
    else {
        nbstands = 10;
    }
}

int Joueur::getNbStands() {
    return nbstands;
}
void Joueur::changerPosition(int case1) {
    position = case1;
}
