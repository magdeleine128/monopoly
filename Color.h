#pragma once
#include <string>
#include <map>
#include <iostream>

class Colors {
private:
    static const std::map<std::string, std::string> colorCodes;

public:
    static std::string colorize(const std::string& text, const std::string& color);
    static void printColored(const std::string& text, const std::string& color);
};
