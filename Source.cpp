#include <iostream>
#include <thread>
#include <chrono>
#include "Joueur.h"
#include "Carte.h"
#include "Plateau.h"

int main() {
    std::cout << "Bienvenue dans Monopoly Junior !" << std::endl;

    Joueur joueur1("ROUGE");
    Joueur joueur2("BLEU");

    Plateau plateau;
    Carte cartesChance;

    joueur1.stand_initialisation(10); // 2 joueurs
    joueur2.stand_initialisation(10);

    bool partieTerminee = false;
    int tour = 0;

    while (!partieTerminee) {
        Joueur& joueurActuel = (tour % 2 == 0) ? joueur1 : joueur2;
        Joueur& autreJoueur = (tour % 2 == 0) ? joueur2 : joueur1;

        std::cout << "\nTour du joueur " << joueurActuel.getCouleur() << std::endl;
        std::cout << " (Argent: " << joueurActuel.getBillets() << " euros)" << std::endl;

        int anciennePosition = joueurActuel.getPosition();
        int de = joueurActuel.lancerDe();
        std::cout << "Dé lancé: " << de << std::endl;

        if ((anciennePosition + de) >= 24) {
            joueurActuel.ajouterArgent(2);
            std::cout << "Vous avez passé par le départ! +2 euros." << std::endl;
        }

        joueurActuel.avancer(de);
        int position = joueurActuel.getPosition();
        std::cout << "Vous êtes maintenant sur la case " << position << std::endl;

        plateau.actionCase(position, joueurActuel, cartesChance);

        if (joueurActuel.getBillets() <= 0) {
            std::cout << "Le joueur " << joueurActuel.getCouleur() << " est en faillite !" << std::endl;
            partieTerminee = true;
        }
        else {
            std::cout << "Attente de 3 secondes avant le prochain tour..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            tour++;
        }
    }

    std::cout << "Fin de la partie." << std::endl;
    return 0;
}
