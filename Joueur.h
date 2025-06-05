#pragma once
#include <vector>
#include <string>
class Joueur {
private:
    std::string couleur;
    int billets;
    int position;
    int nbstands;
    std::vector<int> standPlayer;
public:
    Joueur(std::string clr);
    int lancerDe();
    void payerStand(int montant);
    void acheterStand(int index , int prix);
    bool echangerStand(int case1);//cherche s il possede n et n+1 ou n et n-1 aprés trier le vect
    int getBillets() const;
    void payerJoueur(int montant, Joueur joueur1);
    void ajouterArgent(int montant);
    int getPosition() ;
    void avancer(int nbCases);
    std::string getCouleur();
    void stand_initialisation(int nbjoueur);
    void retirStand(int index);
    int getNbStands();
    void changerPosition(int case1) ;
 

    
};
