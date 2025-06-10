#include "Color.h"

const std::map<std::string, std::string> Colors::colorCodes = {
    {"red", "\033[31m"},
    {"green", "\033[32m"},
    {"yellow", "\033[33m"},
    {"blue", "\033[34m"},
    {"magenta", "\033[35m"},
    {"cyan", "\033[36m"},
    {"white", "\033[37m"},
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
