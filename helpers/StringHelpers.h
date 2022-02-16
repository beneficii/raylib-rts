#pragma once
#include <string>
#include <vector>

namespace MyStrings
{
    const std::string WHITESPACE = " \n\r\t\f\v";
    constexpr auto SEPARATOR = '|';


    std::string ltrim(const std::string& s);

    std::string rtrim(const std::string& s);

    std::string trim(const std::string& s);

    std::string GetString(std::istringstream* stream, char separator = SEPARATOR);

    int GetInt(std::istringstream* stream, char separator = SEPARATOR);

    int GetFloat(std::istringstream* stream, char separator = SEPARATOR);

    std::vector<std::string> GetStringList(std::istringstream* stream, char separator = SEPARATOR, char subSeparator = ';');

    // compile time hash function to enable c++ string switch
    constexpr unsigned int SHash(const char* s, int off = 0)
    {
        return !s[off] ? 5381 : (SHash(s, off + 1) * 33) ^ s[off];
    }
}
