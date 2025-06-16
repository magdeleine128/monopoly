#include <iostream>
#include "Joueur.h"
#include "Carte.h"
#include "Plateau.h"
#include<vector>
#include "Color.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initialisation du générateur aléatoire
    std::cout << Colors::colorize(u8"Bienvenue dans Monopoly Junior du u8 café? !", "jaune") << std::endl;
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
       // if (tour % n == 0) {
            //plateau.afficherPlateau(); } // on l ajoute si on veut afficher  a chaque tour le mise a jour de la crte
        Joueur& joueurActuel = plateau.getJoueur(tour % n);
        std::string couleurJoueur = joueurActuel.getCouleur();

        // Affichage info joueur avec couleur
        std::cout << "\nTour du joueur "
            << Colors::colorize(joueurActuel.getCouleur(), couleurJoueur)
            << " (Argent: " << joueurActuel.getBillets() << " euros)"
            << std::endl;

        // Attente entrée utilisateur (colorée)
        Colors::printColored("Appuyez sur Entree pour lancer le de...", couleurJoueur);
        std::cin.ignore();
        std::cin.get();

        // Lancer de dé (affichage coloré)
        int de = joueurActuel.lancerDe();
        Colors::printColored("De lance: " + std::to_string(de) + "\n", couleurJoueur);

        // Passage départ (message coloré)
        if ((joueurActuel.getPosition() + de) >= 24) {
            joueurActuel.ajouterArgent(2);
            Colors::printColored("Vous avez passe par le depart! +2 euros.\n", couleurJoueur);
        }

        // Déplacement
        joueurActuel.avancer(de);
        Colors::printColored("Vous etes maintenant sur la case " +
            std::to_string(joueurActuel.getPosition()) + "\n",
            couleurJoueur);

        // Action case (la couleur sera gérée dans Plateau.cpp si nécessaire)
        plateau.actionCase(joueurActuel.getPosition(), joueurActuel, cartesChance);

        // Vérification faillite (message en rouge)
        if (joueurActuel.getBillets() <= 0) {
            std::cout << Colors::colorize("Le joueur " + joueurActuel.getCouleur() +
                " est en faillite !", "red")
                << std::endl;
            partieTerminee = true;
        }

        tour++;
    }

    std::cout << Colors::colorize("Fin de la partie.", "magenta") << std::endl;
    return 0;
}
