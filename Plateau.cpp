#include "Joueur.h"
#include "Plateau.h"
#include <algorithm> 
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> // Pour std::runtime_error

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
        {8,   {"amande",      "Banque"}},
        {9,   {"chance",      "Chance"}},
        {10,  {"prison",      "café"}},
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
        {23,  {"propriete",   "Promenade à poney","jaune", 4, 4}},
        {24,  {"amende",      "Banque"}},
        {25,  {"chance",      "Chance"}},
        {26,  {"va_en_prison","Va au café "}},
        {27,  {"propriete",   "Autos tamponneuses", "vert", 4, 4}},
        {28,  {"propriete",   "Grande roue",  "vert", 4, 4}},
        {29,  {"transport",   "Transport"}},
        {30,  {"propriete",   "Grand huit", "bleu marine",5, 5}},
        {31,  {"propriete",   "Montagnes russes",  "bleu marine",5, 5}}
    };
}

void Plateau::ajouterJoueur(Joueur& joueur) {
    MesJoueurs.push_back(joueur);
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

void Plateau::changer_proprio(int index, Joueur joueur) {
    plateau[index].proprietaire = joueur.getCouleur();
}


Joueur& Plateau::trouverParCouleur(const std::string& couleur, std::vector<Joueur>& joueurs) {
    for (auto& joueur : joueurs) {
        if (joueur.getCouleur() == couleur) {
            return joueur;
        }
    }
    throw std::runtime_error("Joueur non trouvé pour la couleur: " + couleur);
}

void Plateau::actionCase(int index, Joueur& joueur, Carte& cartesChance)
{
    Case& c = plateau[index];
    if (c.type == "propriete") {
        if (c.proprietaire == "banque") {
            std::cout << "Ce stand est disponible à l'achat (" << c.prix << "€)" << std::endl;
            std::cout << "Voulez-vous l'acheter ? (o/n) ";
            char choix;
            std::cin >> choix;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (choix == 'o' || choix == 'O') {
                if (joueur.getBillets() >= c.prix) {
                    joueur.acheterStand(index, c.prix);
                    changer_proprio(index, joueur);
                    std::cout << "Félicitations ! Vous avez acheté " << c.nom << std::endl;
                }
                else {
                    std::cout << "Vous n'avez pas assez d'argent pour acheter ce stand." << std::endl;
                }
            }
        }
        else if (c.proprietaire != joueur.getCouleur()) {
            try {
                Joueur proprietaire = trouverParCouleur(c.proprietaire, MesJoueurs);
                int montantAPayer = proprietaire.echangerStand(index) ? c.loyer : 2 * c.loyer;
                joueur.payerStand(montantAPayer);
                proprietaire.ajouterArgent(montantAPayer);
            }
            catch (const std::exception& e) {
                std::cerr << "Erreur: " << e.what() << std::endl;
            }
        }
    }
    else if (c.type == "chance") {
        std::string carte = cartesChance.piocher();
        std::cout << "Vous avez pioché: " << carte << std::endl;
        cartesChance.update();

        if (carte.find("Stand gratuit") != std::string::npos) {
            std::string couleur = carte.substr(14);
            std::vector<int> casesCouleur;

            for (const auto& entry : plateau) {
                const int& idx = entry.first;
                const Case& casePlateau = entry.second;
                if (casePlateau.couleur == couleur) {
                    casesCouleur.push_back(idx);
                }
            }

            if (casesCouleur.size() == 2) {
                int case1 = casesCouleur[0];
                int case2 = casesCouleur[1];

                if (plateau[case1].proprietaire == plateau[case2].proprietaire &&
                    plateau[case1].proprietaire != "banque") {
                    std::cout << "Les 2 stands sont déjà possédés par le même joueur\n";
                }
                else {
                    int choix = (rand() % 2) ? case1 : case2;

                    if (plateau[choix].proprietaire != "banque") {
                        try {
                            Joueur ancienProprio = trouverParCouleur(plateau[choix].proprietaire, MesJoueurs);
                            ancienProprio.retirStand(choix);
                        }
                        catch (...) {
                            // Ignorer si propriétaire non trouvé
                        }
                    }

                    plateau[choix].proprietaire = joueur.getCouleur();
                    joueur.acheterStand(choix, 0);
                    std::cout << "Vous obtenez le stand " << plateau[choix].nom << " gratuitement!\n";
                }
            }
        }
        else if (carte == "Va sur la case Toboggan aquatique") {
            joueur.changerPosition(14);
        }
        else if (carte == "Va sur la case Grand Huit") {
            joueur.changerPosition(30);
        }
        else if (carte == "Paie 3 euros pour prendre le bus qui te conduit au café") {
            joueur.payerStand(3);
            joueur.changerPosition(10);
            fortune = +3;
        }
        else if (carte == "Va sur la case départ et reçois 2 euros") {
            joueur.changerPosition(0);
            joueur.ajouterArgent(2);
        }
        else if (carte == "Va sur la case Ballet des dauphins et paie 2 euros") {
            joueur.changerPosition(24);
            joueur.payerStand(2);
        }
        else if (carte == "Va sur la case Feu d'artifice et paie 2 euros") {
            joueur.changerPosition(8);
            joueur.payerStand(2);
        }
        else if (carte == "Prends le petit train bleu et relance le dé") {
            joueur.changerPosition(21);
            int de = joueur.lancerDe();
            joueur.avancer(de);
            actionCase(joueur.getPosition(), joueur, cartesChance);
        }
        else if (carte == "Prends le petit train rouge et relance le dé") {
            joueur.changerPosition(29);
            int de = joueur.lancerDe();
            joueur.avancer(de);
            actionCase(joueur.getPosition(), joueur, cartesChance);
        }
        else if (carte == "Prends le petit train jaune et relance le dé") {
            joueur.changerPosition(5);
            int de = joueur.lancerDe();
            joueur.avancer(de);
            actionCase(joueur.getPosition(), joueur, cartesChance);
        }
        else if (carte == "Prends le petit train vert et relance le dé") {
            joueur.changerPosition(13);
            int de = joueur.lancerDe();
            joueur.avancer(de);
            actionCase(joueur.getPosition(), joueur, cartesChance);
        }
    }
    else if (c.type == "transport") {// le cas ou on se trouve dans une case  de transport 
        int de = joueur.lancerDe();
        joueur.avancer(de);
        actionCase(joueur.getPosition(), joueur, cartesChance);

    }
    else if (c.nom == "café") {

    }
    else if (c.nom == "Va au café") {

        joueur.payerStand(3);
        joueur.changerPosition(10);
        fortune = +3;
    }
    else if (c.nom == "Fortune") {

        joueur.ajouterArgent(fortune);
        fortune = 0;
    }
    else if (c.type == "amende") {

        joueur.payerStand(2);

    }



}
