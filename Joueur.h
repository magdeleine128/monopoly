#pragma once
#include <vector>

class Joueur {
public:
    enum Couleur { ROUGE, BLEU, VERT, JAUNE, AUCUN };
    Joueur(Couleur couleur);
    int lancerDe();
    void payerStand(int montant);
    void acheterStand(int index, int prix);
    bool echangerStand(int case1);//cherche s il possede n et n+1 ou n et n-1 aprés trier le vect
    int getBillets() const;
    void payerJoueur(int montant);
    void ajouterArgent(int montant);
    int getPosition();
    void avancer(int nbCases);
    Couleur getCouleur() const;
    void stand_initialisation(int nbjoueur);
    void retirStand(int index);
    int getNbStands(); // Déclaration ajoutée
    void changerPosition(int case1);
private:
    Couleur couleur;
    int billets;
    int position;
    int nbstands;
    std::vector<int> standPlayer;
};
