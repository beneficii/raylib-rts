#include "StringHelpers.h"

#include <sstream>
#include <iostream>

std::string MyStrings::ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string MyStrings::rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string MyStrings::trim(const std::string& s) {
    return rtrim(ltrim(s));
}

std::string MyStrings::GetString(std::istringstream* stream, char separator)
{
    std::string token;
    std::getline(*stream, token, separator);

    return MyStrings::trim(token);
}

int MyStrings::GetInt(std::istringstream* stream, char separator)
{
    std::string token;
    std::getline(*stream, token, separator);

    if (token.empty()) return 0;

    return std::stoi(token);
}

int MyStrings::GetFloat(std::istringstream* stream, char separator)
{
    std::string token;
    std::getline(*stream, token, separator);

    if (token.empty()) return 0;

    return std::stof(token);
}

std::vector<std::string> MyStrings::GetStringList(std::istringstream* stream, char separator, char subSeparator)
{
    std::string token;
    std::getline(*stream, token, separator);

    std::istringstream ss(token);
    std::string subtoken;
    std::vector<std::string> result;

    while (getline(ss, subtoken, subSeparator)) {
        if (subtoken.empty()) continue;

        result.push_back(MyStrings::trim(subtoken));
    }

    return result;
}
