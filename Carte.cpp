#include "Carte.h"
#include <algorithm> // pour std::shuffle
#include <random>    // pour std::random_device et std::mt19937

Carte::Carte() {
    // 2 cartes pour chaque stand gratuit
    cartes.push_back("Stand gratuit orange");
    cartes.push_back("Stand gratuit orange");
    cartes.push_back("Stand gratuit rouge");
    cartes.push_back("Stand gratuit rouge");
    cartes.push_back("Stand gratuit rose");
    cartes.push_back("Stand gratuit rose");
    cartes.push_back("Stand gratuit bleu clair");
    cartes.push_back("Stand gratuit bleu clair");
    cartes.push_back("Stand gratuit bleu foncé");
    cartes.push_back("Stand gratuit bleu foncé");
    cartes.push_back("Stand gratuit jaune");
    cartes.push_back("Stand gratuit jaune");
    cartes.push_back("Stand gratuit vert");
    cartes.push_back("Stand gratuit vert");

    // 1 stand gratuit violet
    cartes.push_back("Stand gratuit violet");

    // Autres cartes spéciales
    cartes.push_back("Va sur la case Toboggan aquatique");
    cartes.push_back("Va sur la case Grand Huit");
    cartes.push_back("Paie 3 euros pour prendre le bus qui te conduit au café");
    cartes.push_back("Va sur la case départ et reçois 2 euros");
    cartes.push_back("Va sur la case Ballet des dauphins et paie 2 euros");
    cartes.push_back("Va sur la case Feu d'artifice et paie 2 euros");

    cartes.push_back("Prends le petit train bleu et relance le dé");
    cartes.push_back("Prends le petit train rouge et relance le dé");
    cartes.push_back("Prends le petit train jaune et relance le dé");
    cartes.push_back("Prends le petit train vert et relance le dé");

    melangerCartes(cartes); // Shuffler à l'initialisation
}
std::string Carte::piocher() {

    return cartes[0];
}

void Carte::update() {

    std::string premier = cartes.front();//STOKER PREMIERE CARTE
    cartes.erase(cartes.begin());//EFFACER PREMIERE CARTE =>nb des cartes n-1
    cartes.push_back(premier);

}

void Carte::melangerCartes(std::vector<std::string>& cartes) {
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(cartes.begin(), cartes.end(), g);
}
