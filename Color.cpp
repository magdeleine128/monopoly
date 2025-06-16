#include "Color.h"

const std::map<std::string, std::string> Colors::colorCodes = {
   
    {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},
    {"rouge", "\033[31m"},
    {"vert", "\033[32m"},
    {"jaune", "\033[33m"},
    {"bleu", "\033[34m"},
    {"violet", "\033[35m"},
    {"rose", "\033[38;5;206m"},
    {"bleu clair", "\033[36m"},
    {"bleu marine", "\033[34m"}
};

std::string Colors::colorize(const std::string& text, const std::string& color) {
    auto it = colorCodes.find(color);
    if (it != colorCodes.end()) {
        return it->second + text + "\033[0m";
    }
    return text;
}

void Colors::printColored(const std::string& text, const std::string& color) {
    std::cout << colorize(text, color);
}
