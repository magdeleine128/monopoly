#include <iostream>
#include "Joueur.h"
#include "Carte.h"
#include "Plateau.h"

int main() {
    std::cout << "Bienvenue dans Monopoly Junior !" << std::endl;

    Joueur joueur1(Joueur::ROUGE);
    Joueur joueur2(Joueur::BLEU);

    Plateau plateau;
    Carte cartesChance;

    joueur1.stand_initialisation(2); // 2 joueurs
    joueur2.stand_initialisation(2);

    bool partieTerminee = false;
    int tour = 0;

    while (!partieTerminee) {
        Joueur& joueurActuel = (tour % 2 == 0) ? joueur1 : joueur2;
        Joueur& autreJoueur = (tour % 2 == 0) ? joueur2 : joueur1;

        // Affichage couleur et argent
        std::string couleurStr;
        switch (joueurActuel.getCouleur()) {
        case Joueur::ROUGE: couleurStr = "Rouge"; break;
        case Joueur::BLEU:  couleurStr = "Bleu";  break;
        case Joueur::VERT:  couleurStr = "Vert";  break;
        case Joueur::JAUNE: couleurStr = "Jaune"; break;
        }
        std::cout << "\nTour du joueur " << couleurStr;
        std::cout << " (Argent: " << joueurActuel.getBillets() << " euros)" << std::endl;

        int anciennePosition = joueurActuel.getPosition();
        int de = joueurActuel.lancerDe();
        std::cout << "De lance: " << de << std::endl;

        // Don de 2€ si passage par le départ
        if ((anciennePosition + de) >= 24) {
            joueurActuel.ajouterArgent(2);
            std::cout << "Vous avez passe par le depart! +2 euros." << std::endl;
        }

        joueurActuel.avancer(de);
        int position = joueurActuel.getPosition();
        std::cout << "Vous etes maintenant sur la case " << position << std::endl;

        plateau.actionCase(position, joueurActuel, autreJoueur, cartesChance);

        // Vérification faillite
        if (joueurActuel.getBillets() <= 0) {
            std::cout << "Le joueur " << couleurStr << " est en faillite !" << std::endl;
            partieTerminee = true;
        }

        tour++;
    }

    std::cout << "Fin de la partie." << std::endl;
    return 0;
}