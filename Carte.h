#pragma once
#include <string>
#include <vector>
class Carte {
public:
    Carte();
    std::string piocher();
    void update();
    void intisialiser();

private:
    std::vector<std::string> vec_carte;
};
