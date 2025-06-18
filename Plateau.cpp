#include "Joueur.h"
#include "Plateau.h"
#include <algorithm> 
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> // Pour std::runtime_error

Plateau::Plateau() {
    plateau = {
        {0,   {"depart",      "Depart"}},
        {1,   {"chance",      "Chance"}},
        {2,   {"propriete",   "\033[35mJeu de ballons\033[0m", "violet", 1, 1}},
        {3,   {"propriete",   "\033[35mBarbe a papa\033[0m", "violet", 1, 1}},
        {4,   {"chance",      "Chance"}},
        {5,   {"transport",   "Transport"}},
        {6,   {"propriete",   "\033[36mTheatre de marionnettes\033[0m", "bleu clair", 2, 2}},
        {7,   {"propriete",   "\033[36mSpectacle de magie\033[0m", "bleu clair", 2, 2}},
        {8,   {"amande",      "Banque"}},
        {9,   {"chance",      "Chance"}},
        {10,  {"prison",      "Cafe"}},
        {11,  {"propriete",   "\033[38;5;206mManege\033[0m", "rose", 2, 2}},
        {12,  {"propriete",   "\033[38;5;206mPedalos\033[0m", "rose", 2, 2}},
        {13,  {"transport",   "Transport"}},
        {14,  {"propriete",   "\033[33mToboggan aquatique\033[0m", "orange", 3, 3}},
        {15,  {"propriete",   "\033[33mMini Golf\033[0m", "orange", 3, 3}},
        {16,  {"fortune",     "Fortune"}},
        {17,  {"chance",      "Chance"}},
        {18,  {"propriete",   "\033[31mJeux video\033[0m", "rouge", 3, 3}},
        {19,  {"propriete",   "\033[31mMaison hantee\033[0m", "rouge", 3, 3}},
        {20,  {"chance",      "Chance"}},
        {21,  {"transport",   "Transport"}},
        {22,  {"propriete",   "\033[33mPromenade en hélicoptere\033[0m", "jaune", 4, 4}},
        {23,  {"propriete",   "\033[33mPromenade a poney\033[0m", "jaune", 4, 4}},
        {24,  {"amende",      "Banque"}},
        {25,  {"chance",      "Chance"}},
        {26,  {"va_en_prison","Va au cafe"}},
        {27,  {"propriete",   "\033[32mAutos tamponneuses\033[0m", "vert", 4, 4}},
        {28,  {"propriete",   "\033[32mGrande roue\033[0m", "vert", 4, 4}},
        {29,  {"transport",   "Transport"}},
        {30,  {"propriete",   "\033[34mGrand huit\033[0m", "bleu marine", 5, 5}},
        {31,  {"propriete",   "\033[34mMontagnes russes\033[0m", "bleu marine", 5, 5}}
    };
}

void Plateau::ajouterJoueur(Joueur& joueur) {
    MesJoueurs.push_back(joueur);
}
void Plateau::definePlayers(int n) {
    for (int i = 1; i <= n; i++) {
        std::string couleur;
        std::cout << "Couleur du joueur n°" << i << ": ";
        std::cin >> couleur;

        Joueur nouveauJoueur(couleur);
        nouveauJoueur.stand_initialisation(n);
        ajouterJoueur(nouveauJoueur);
    }

}
Joueur& Plateau::getJoueur(int index) {
    if (index < 0 || index >= MesJoueurs.size()) {
        throw std::out_of_range("Index de joueur invalide");
    }
    return MesJoueurs[index];
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
    throw std::runtime_error("Joueur non trouve pour la couleur: " + couleur);
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
                    std::cout << "Felicitations ! Vous avez achete " << c.nom << std::endl;
                }
                else {
                    std::cout << "Vous n'avez pas assez d'argent pour acheter ce stand." << std::endl;
                }
            }
        }
        else if (c.proprietaire != joueur.getCouleur()) {
            try {
                Joueur& proprietaire = trouverParCouleur(c.proprietaire, MesJoueurs);
                bool doubleLoyer = !proprietaire.echangerStand(index);
                int montantAPayer = doubleLoyer ? 2 * c.loyer : c.loyer;

                // Nouveaux messages d'information
                std::cout << "Ce stand appartient au joueur " << c.proprietaire << "!" << std::endl;
                if (doubleLoyer) {
                    std::cout << "Le proprietaire possede les 2 stands de cette couleur, vous payez double loyer!" << std::endl;
                }
                std::cout << "Vous payez " << montantAPayer << "€ au joueur " << c.proprietaire << std::endl;

                joueur.payerStand(montantAPayer);
                proprietaire.ajouterArgent(montantAPayer);

                std::cout << "Votre argent restant: " << joueur.getBillets() << "€" << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Erreur: " << e.what() << std::endl;
            }
        }
        else {
            std::cout << "Ce stand vous appartient deja!" << std::endl;
        }
    }
    else if (c.type == "chance") {
        std::string carte = cartesChance.piocher();
        std::cout << "Vous avez pioche: " << carte << std::endl;
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
                    std::cout << "Les 2 stands sont deja possedes par le meme joueur" << std::endl;
                }
                else {
                    int choix = (rand() % 2) ? case1 : case2;

                    if (plateau[choix].proprietaire != "banque") {
                        try {
                            Joueur ancienProprio = trouverParCouleur(plateau[choix].proprietaire, MesJoueurs);
                            ancienProprio.retirStand(choix);
                            std::cout << "Vous prenez le stand " << plateau[choix].nom << " au joueur " << plateau[choix].proprietaire << std::endl;
                        }
                        catch (...) {
                            // Ignorer si propriétaire non trouvé
                        }
                    }

                    plateau[choix].proprietaire = joueur.getCouleur();
                    joueur.acheterStand(choix, 0);
                    std::cout << "Vous obtenez le stand " << plateau[choix].nom << " gratuitement!" << std::endl;
                }
            }
        }
        else if (carte == "Va sur la case Toboggan aquatique") {
            std::cout << "Vous allez directement au Toboggan aquatique!" << std::endl;
            joueur.changerPosition(14);
        }
        else if (carte == "Va sur la case Grand Huit") {
            std::cout << "Vous allez directement au Grand Huit!" << std::endl;
            joueur.changerPosition(30);
        }
        else if (carte == "Paie 3 euros pour prendre le bus qui te conduit au cafe") {
            std::cout << "Vous payez 3€ pour prendre le bus vers le cafe" << std::endl;
            joueur.payerStand(3);
            joueur.changerPosition(10);
            fortune += 3;
        }
        else if (carte == "Va sur la case départ et reçois 2 euros") {
            std::cout << "Vous retournez à la case départ et recevez 2€!" << std::endl;
            joueur.changerPosition(0);
            joueur.ajouterArgent(2);
        }
        else if (carte == "Va sur la case Ballet des dauphins et paie 2 euros") {
            std::cout << "Vous allez au Ballet des dauphins et payez 2€" << std::endl;
            joueur.changerPosition(24);
            joueur.payerStand(2);
        }
        else if (carte == "Va sur la case Feu d'artifice et paie 2 euros") {
            std::cout << "Vous allez au Feu d'artifice et payez 2€" << std::endl;
            joueur.changerPosition(8);
            joueur.payerStand(2);
        }
        else if (carte.find("Prends le petit train") != std::string::npos) {
            std::cout << "Vous prenez un train et relancez le de!" << std::endl;
            int nouvellePosition = 0;
            if (carte.find("bleu") != std::string::npos) nouvellePosition = 21;
            else if (carte.find("rouge") != std::string::npos) nouvellePosition = 29;
            else if (carte.find("jaune") != std::string::npos) nouvellePosition = 5;
            else if (carte.find("vert") != std::string::npos) nouvellePosition = 13;

            joueur.changerPosition(nouvellePosition);
            std::cout << "Vous etes maintenant sur la case " << joueur.getPosition() << " (gare)" << std::endl;

            std::cout << "Appuyez sur Entree pour lancer le de..." << std::endl;
            std::cin.ignore();
            std::cin.get();

            int de = joueur.lancerDe();
            std::cout << "Nouveau lancer de de: " << de << std::endl;
            joueur.avancer(de);
            std::cout << "Vous êtes maintenant sur la case " << joueur.getPosition() << std::endl;
            actionCase(joueur.getPosition(), joueur, cartesChance);
        }
    }
    else if (c.type == "transport") {
        std::cout << "Vous prenez un transport et relancez le de!" << std::endl;
        std::cout << "Appuyez sur Entree pour lancer le de..." << std::endl;
        std::cin.ignore();
        std::cin.get();

        int de = joueur.lancerDe();
        std::cout << "Nouveau lancer de de: " << de << std::endl;
        joueur.avancer(de);
        std::cout << "Vous êtes maintenant sur la case " << joueur.getPosition() << std::endl;
        actionCase(joueur.getPosition(), joueur, cartesChance);
    }
    else if (c.nom == "café") {
        std::cout << "Vous etes au cafe. Rien ne se passe." << std::endl;
    }
    else if (c.nom == "Va au café") {
        std::cout << "Vous devez aller au cafe et payer 3€!" << std::endl;
        joueur.payerStand(3);
        joueur.changerPosition(10);
        fortune += 3;
    }
    else if (c.nom == "Fortune") {
        if (fortune > 0) {
            std::cout << "Vous recevez " << fortune << "€ de la fortune!" << std::endl;
            joueur.ajouterArgent(fortune);
            fortune = 0;
        }
        else {
            std::cout << "La fortune est vide pour le moment." << std::endl;
        }
    }
    else if (c.type == "amende") {
        std::cout << "Vous payez une amende de 2€ à la banque!" << std::endl;
        joueur.payerStand(2);
        std::cout << "Votre argent restant: " << joueur.getBillets() << "€" << std::endl;
}
    else if (c.type == "depart") {
        std::cout << "Vous etes sur la case depart." << std::endl;
    }
}
