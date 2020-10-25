#pragma once
#include <vector>
#include <string>
#include <iterator>
#include <regex>

class Tokenizer
{
	public:
		std::vector<std::vector<std::string>> tokenize(std::vector<std::string>& lines);
};

