#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <map>

class Interpreter
{
private:
	const std::string ETX = "\u0003";
	std::ostream* outstream;
	std::vector<std::string> tokens;
	int pos = -1;
	std::string printType;
	std::map<std::string, int> varMap;

	std::string peek();
	std::string peek(int steps);
	void consume(const std::string& token);

	//Parsing methods.
	void parse_Stmt();
	void parse_ConfigStmt();
	void parse_PrintStmt();
	void parse_AssgStmt();

	int parse_MathExp();
	int parse_SumExp();
	int parse_ProductExp();
	int parse_PrimaryExp();
public:
	Interpreter(std::ostream& out_stream);
	void evaluate(const std::vector<std::string>& tokens);
};

