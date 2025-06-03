#include "Plateau.h"
#include <iostream>
#include "Joueur.h"
#include <string>

Plateau::Plateau() {
    plateau = {
          {0,   {"depart",      "Départ"}},
 {1,   {"chance",      "Chance"}},
 {2,   {"propriete",   "Jeu de ballons","violet", 1, 1}},
 {3,   {"propriete",   "Barbe à papa","violet", 1, 1}},
 {4,   {"chance",      "Chance"}},
 {5,   {"transport",   "Transport"}},
 {6,   {"propriete",   "Theatre de marionnettes", "bleu clair", 2, 2}},
 {7,   {"propriete",   "Spectacle de magie", "bleu clair",2, 2}},
 {8,   {"banque",      "Banque"}},
 {9,   {"chance",      "Chance"}},
 {10,  {"prison",      "Prison"}},
 {11,  {"propriete",   "Manege", "rose", 2, 2}},
 {12,  {"propriete",   "Pedalos","rose", 2, 2}},
 {13,  {"transport",   "Transport"}},
 {14,  {"propriete",   "Toboggan aqquatique", "orange",3, 3}},
 {15,  {"propriete",   "mini Golf","orange", 3, 3}},
 {16,  {"fortune",     "Fortune"}},
 {17,  {"chance",      "Chance"}},
 {18,  {"propriete",   "Jeux vidéo","rouge",  3, 3}},
 {19,  {"propriete",   "Maison hantée","rouge",3, 3}},
 {20,  {"chance",      "Chance"}},
 {21,  {"transport",   "Transport"}},
 {22,  {"propriete",   "Promenade en hélicoptère","jaune", 4, 4}},
 {23,  {"propriete",   "Promenade à  poney","jaune", 4, 4}},
 {24,  {"banque",      "Banque"}},
 {25,  {"chance",      "Chance"}},
 {26,  {"va_en_prison","Va en prison"}},
 {27,  {"propriete",   "Autos tamponneuses", "vert", 4, 4}},
 {28,  {"propriete",   "Grande roue",  "vert", 4, 4}},
 {29,  {"transport",   "Transport"}},
 {30,  {"propriete",   "Grand huit", "bleu marine",5, 5}},
 {31,  {"propriete",   "Montagnes russes",  "bleu marine",5, 5}},
    };
}

void Plateau::afficherPlateau() const {
    for (const auto& entry : plateau) {
        const Case& c = entry.second;
        std::cout << "Case " << entry.first << ": " << c.nom << " (Type: " << c.type;

        if (!c.couleur.empty())
            std::cout << ", Couleur: " << c.couleur;

        if (c.prix > 0)
            std::cout << ", Prix: " << c.prix;

        if (c.loyer > 0)
            std::cout << ", Loyer: " << c.loyer;

        std::cout << ", Propriétaire: " << c.proprietaire;
        std::cout << ")\n";
    }
}

int Plateau::getLoyer(int index) {
    return plateau[index].loyer;
}

std::string Plateau::getOwner(int index) {
    return plateau[index].proprietaire;
}

int Plateau::getPrix(int index) {
    return plateau[index].prix;
}

std::string Plateau::getType(int index) {
    return plateau[index].type;
}

std::string Plateau::getcolor(int index) {
    return plateau[index].couleur;
}

void Plateau::actionCase(int index, Joueur& joueur, Carte& cartesChance) {
    Case& c = plateau[index];  // non-const pour pouvoir modifier le propriétaire

    if (c.type == "chance") {
        std::string carte = cartesChance.piocher();
        std::cout << "Vous avez pioché: " << carte << std::endl;
        cartesChance.update();

        if (carte.find("Stand gratuit") != std::string::npos) {
            std::cout << "Vous avez obtenu un " << carte << " !" << std::endl;
        }
        else if (carte == "Va sur la case Toboggan aquatique") {
            joueur.avancer(3);
        }
        else if (carte == "Va sur la case Grand Huit") {
            joueur.avancer(5);
        }
        else if (carte == "Paie 3 euros pour prendre le bus qui te conduit au café") {
            joueur.payerStand(3);
        }
        else if (carte == "Va sur la case départ et reçois 2 euros") {
            joueur.avancer(0);
            joueur.ajouterArgent(2);
        }
        else if (carte == "Va sur la case Ballet des dauphins et paie 2 euros") {
            joueur.avancer(10);
            joueur.payerStand(2);
        }
        else if (carte == "Va sur la case Feu d'artifice et paie 2 euros") {
            joueur.avancer(12);
            joueur.payerStand(2);
        }
        else if (carte.find("relance le dé") != std::string::npos) {
            std::cout << "Vous prenez le petit train et relancez le dé !" << std::endl;
            int de = joueur.lancerDe();
            joueur.avancer(de);
        }
    }
    else if (c.type == "propriete") {
        if (c.proprietaire == "banque") {
            std::cout << "Cette case est disponible à l'achat pour " << c.prix << " euros." << std::endl;
            if (joueur.getBillets() >= c.prix && joueur.echangerStand(index)) {
                joueur.acheterStand(index, c.prix);
                c.proprietaire = joueur.getCouleur();
            }
            else {
                std::cout << "Achat impossible (fonds insuffisants ou propriété adjacente)." << std::endl;
            }
        }
        else if (c.proprietaire != joueur.getCouleur()) {
            std::cout << "Cette case appartient à " << c.proprietaire << ". Vous devez payer " << c.loyer << " euros de loyer." << std::endl;
            joueur.payerStand(c.loyer);
        }
        else {
            std::cout << "C'est votre propre propriété." << std::endl;
        }
    }
}
