#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Joueur.h"
#include "Carte.h"

struct Case {
    std::string type = "";
    std::string nom = "";
    std::string couleur = "";
    int prix = 0;
    int loyer = 0;
    std::string proprietaire = "banque";
};

class Plateau {
public:
    Plateau();
    int getLoyer(int index);
    int getPrix(int index);
    std::string getOwner(int index);
    std::string getType(int index);
    std::string getcolor(int index);
    void afficherPlateau() const;
    void actionCase(int index, Joueur& joueur, Carte& cartesChance);
private:
    std::map<int, Case> plateau;
    Carte cartesChance;
};