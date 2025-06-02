#pragma once
#include <string>
#include <vector>

class Carte {
public:
    Carte();
    std::string piocher();
    void update();
 
    void melangerCartes(std::vector<std::string>& cartes);
private:
    std::vector<std::string> cartes;
};
