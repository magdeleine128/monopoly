#include "Plateau.h"
#include <iostream>

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
void Plateau::actionCase(int index, Joueur& joueur , Carte& cartesChance) {
    const Case& c = plateau[index];

    if (c.type == "chance") {
        // Piocher une carte chance
        std::string carteChance = cartesChance.piocher(); // Piocher la carte chance
        std::cout << "Vous avez pioché: " << carteChance << std::endl;

        // Exécuter l'action de la carte chance
        if (carteChance == "Stand gratuit orange" || carteChance == "Stand gratuit rouge" ||
            carteChance == "Stand gratuit rose" || carteChance == "Stand gratuit bleu clair" ||
            carteChance == "Stand gratuit bleu foncé" || carteChance == "Stand gratuit jaune" ||
            carteChance == "Stand gratuit vert" || carteChance == "Stand gratuit violet") {
            // Logique pour obtenir un stand gratuit
            std::cout << "Vous avez obtenu un " << carteChance << " !" << std::endl;
            // Ici, vous pouvez ajouter la logique pour donner le stand au joueur
            // Par exemple, ajouter le stand à la liste des stands du joueur

        }
        else if (carteChance == "Va sur la case Toboggan aquatique") {
            joueur.avancer(3); // Avancer de 3 cases
        }
        else if (carteChance == "Va sur la case Grand Huit") {
            joueur.avancer(5); // Avancer de 5 cases
        }
        else if (carteChance == "Paie 3 euros pour prendre le bus qui te conduit au café") {
            joueur.payerStand(3); // Payer 3 euros
        }
        else if (carteChance == "Va sur la case départ et reçois 2 euros") {
            joueur.avancer(0); // Retourner à la case départ
            joueur.ajouterArgent(2); // Recevoir 2 euros
        }
        else if (carteChance == "Va sur la case Ballet des dauphins et paie 2 euros") {
            joueur.avancer(10); // Avancer à la case Ballet des dauphins (index 10 par exemple)
            joueur.payerStand(2); // Payer 2 euros
        }
        else if (carteChance == "Va sur la case Feu d'artifice et paie 2 euros") {
            joueur.avancer(12); // Avancer à la case Feu d'artifice (index 12 par exemple)
            joueur.payerStand(2); // Payer 2 euros
        }
        else if (carteChance == "Prends le petit train bleu et relance le dé") {
            std::cout << "Vous prenez le petit train bleu et relancez le dé !" << std::endl;
            int de = joueur.lancerDe(); // Relancer le dé
            joueur.avancer(de); // Avancer du nombre de cases obtenu
        }
        else if (carteChance == "Prends le petit train rouge et relance le dé") {
            std::cout << "Vous prenez le petit train rouge et relancez le dé !" << std::endl;
            int de = joueur.lancerDe(); // Relancer le dé
            joueur.avancer(de); // Avancer du nombre de cases obtenu
        }
        else if (carteChance == "Prends le petit train jaune et relance le dé") {
            std::cout << "Vous prenez le petit train jaune et relancez le dé !" << std::endl;
            int de = joueur.lancerDe(); // Relancer le dé
            joueur.avancer(de); // Avancer du nombre de cases obtenu
        }
        else if (carteChance == "Prends le petit train vert et relance le dé") {
            std::cout << "Vous prenez le petit train vert et relancez le dé !" << std::endl;
            int de = joueur.lancerDe(); // Relancer le dé
            joueur.avancer(de); // Avancer du nombre de cases obtenu
        }
    }
}
