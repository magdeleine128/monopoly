#include <iostream>
#include "Joueur.h"
#include "Carte.h"
#include "Plateau.h"
#include<vector>


int main() {
    std::cout << "Bienvenue dans Monopoly Junior !" << std::endl;

    Joueur joueur1("ROUGE");
    Joueur joueur2("BLEU");
    Plateau plateau;
    Carte cartesChance;

    joueur1.stand_initialisation(2); // 2 joueurs
    joueur2.stand_initialisation(2);
    plateau.ajouterJoueur(joueur1);
    plateau.ajouterJoueur(joueur2);
    bool partieTerminee = false;
    int tour = 0;
    // Affichage plateau
    plateau.afficherPlateau();
    while (!partieTerminee) {
        Joueur& joueurActuel = (tour % 2 == 0) ? joueur1 : joueur2;

        // Affichage info joueur
        std::cout << "\nTour du joueur " << joueurActuel.getCouleur()
            << " (Argent: " << joueurActuel.getBillets() << " euros)" << std::endl;

        

        // Attente entrée utilisateur
        std::cout << "Appuyez sur Entree pour lancer le de...";
        std::cin.ignore();
        std::cin.get();

        // Lancer de dé
        int de = joueurActuel.lancerDe();
        std::cout << "De lance: " << de << std::endl;

        // Passage départ
        if ((joueurActuel.getPosition() + de) >= 24) {
            joueurActuel.ajouterArgent(2);
            std::cout << "Vous avez passe par le depart! +2 euros." << std::endl;
        }

        // Déplacement
        joueurActuel.avancer(de);
        std::cout << "Vous etes maintenant sur la case " << joueurActuel.getPosition() << std::endl;

        // Action case
        plateau.actionCase(joueurActuel.getPosition(), joueurActuel, cartesChance);

        // Vérification faillite
        if (joueurActuel.getBillets() <= 0) {
            std::cout << "Le joueur " << joueurActuel.getCouleur() << " est en faillite !" << std::endl;
            partieTerminee = true;
        }

        tour++;
    }

    std::cout << "Fin de la partie." << std::endl;
    return 0;
}
