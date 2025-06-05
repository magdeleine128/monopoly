#pragma once
#include <map>
#include <string>
#include <iostream>
#include "Joueur.h"
#include "Carte.h"
#include<vector>

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
    
   
    
    void afficherPlateau() const;
    void actionCase(int index, Joueur& joueur, Carte& cartesChance);
    void changer_proprio(int index, Joueur joueur);
    void ajouterJoueur( Joueur& joueur);
    Joueur& trouverParCouleur(const std::string& couleur, std::vector<Joueur>& joueurs);
private:
    std::map<int, Case> plateau;
    Carte cartesChance;
    std::vector< Joueur> MesJoueurs ;
    int fortune=0;
};
