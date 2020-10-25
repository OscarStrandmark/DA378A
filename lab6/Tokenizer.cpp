#include "Tokenizer.h"
#include <iostream>
#include <regex>
#include <vector>

/*
This is some black magic shit.
Source:
https://stackoverflow.com/a/27468529/7891570
*/

std::vector<std::vector<std::string>> Tokenizer::tokenize(std::vector<std::string>& lines)
{
    std::vector<std::vector<std::string>> tokenized_lines; //Return item

    std::regex reg("\\s+"); //Regex for any amount of whitespace characters, the extra '\' is to escape special character. (I think)

    for (std::string str : lines)
    {
        std::sregex_token_iterator iter(str.begin(), str.end(), reg, -1); //'-1' tells the iterator to only include parts are between the matches
        std::sregex_token_iterator end;

        std::vector<std::string> v(iter, end);

        tokenized_lines.push_back(v);
    }

    return tokenized_lines;
}

