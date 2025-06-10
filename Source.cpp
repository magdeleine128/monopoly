#include <iostream>
#include "Joueur.h"
#include "Carte.h"
#include "Plateau.h"
#include<vector>


int main() {
    std::cout << "Bienvenue dans Monopoly Junior !" << std::endl;
    std::cout << "Vous etes combien de joueurs? ";
    int n;
    std::cin >> n;
    std::cin.ignore();  // Pour vider le buffer

    Plateau plateau;
    Carte cartesChance;

    // Création des joueurs
    plateau.definePlayers(n);

    bool partieTerminee = false;
    int tour = 0;

    plateau.afficherPlateau();
    while (!partieTerminee) {
        Joueur& joueurActuel = plateau.getJoueur(tour % n);

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
