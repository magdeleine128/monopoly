#include "Carte.h"
#include <algorithm> // pour std::shuffle
#include <random>    // pour std::random_device et std::mt19937
Carte::Carte(){

    // 2 cartes pour chaque stand gratuit
    cartes.push_back("Stand gratuit orange");
    cartes.push_back("Stand gratuit orange");

    cartes.push_back("Stand gratuit rouge");
    cartes.push_back("Stand gratuit rouge");

    cartes.push_back("Stand gratuit rose");
    cartes.push_back("Stand gratuit rose");

    cartes.push_back("Stand gratuit bleu clair");
    cartes.push_back("Stand gratuit bleu clair");

    cartes.push_back("Stand gratuit bleu fonc�");
    cartes.push_back("Stand gratuit bleu fonc�");

    cartes.push_back("Stand gratuit jaune");
    cartes.push_back("Stand gratuit jaune");

    cartes.push_back("Stand gratuit vert");
    cartes.push_back("Stand gratuit vert");

    // 1 stand gratuit violet
    cartes.push_back("Stand gratuit violet");

    // Autres cartes sp�ciales
    cartes.push_back("Va sur la case Toboggan aquatique");
    cartes.push_back("Va sur la case Grand Huit");
    cartes.push_back("Paie 3 euros pour prendre le bus qui te conduit au caf�");
    cartes.push_back("Va sur la case d�part et re�ois 2 euros");
    cartes.push_back("Va sur la case Ballet des dauphins et paie 2 euros");
    cartes.push_back("Va sur la case Feu d'artifice et paie 2 euros");

    cartes.push_back("Prends le petit train bleu et relance le d�");
    cartes.push_back("Prends le petit train rouge et relance le d�");
    cartes.push_back("Prends le petit train jaune et relance le d�");
    cartes.push_back("Prends le petit train vert et relance le d�");
}

std::string Carte::piocher()  {
    
    return vec_carte[0];
}
void Carte::update() {
    std::string premier = mots[0];// sauvegarde du premier

    // D�calage � gauche
    for (size_t i = 1; i < vec_carte.size(); ++i) {
        mots[i - 1] = mots[i];
    }

    // Mise du premier �l�ment � la fin
    mots[mots.size() - 1] = premier;
}
}void melangerCartes(std::vector<std::string>& cartes) {
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(cartes.begin(), cartes.end(), g);
}