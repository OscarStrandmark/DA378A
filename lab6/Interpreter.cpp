#include "Interpreter.h"
#include <regex>
#include <bitset>

Interpreter::Interpreter(std::ostream& out_stream)
{
	outstream = &out_stream;
}

void Interpreter::evaluate(const std::vector<std::string> &tokens)
{
	this->tokens = tokens;
	pos = 0;

	parse_Stmt();
}

std::string Interpreter::peek()
{
	return peek(0);
}

std::string Interpreter::peek(int steps)
{
	if (pos + steps >= tokens.size()) return ETX;

	return tokens[pos + steps];
}

void Interpreter::consume(const std::string& token)
{
	std::string next_token = peek();
	if (next_token == ETX) throw std::runtime_error("Consumed past last token\n");
	if (next_token != token) throw std::runtime_error("Could not consume token " + token + "\n");

	++pos;
}

void Interpreter::parse_Stmt()
{
	std::string next_token = peek();
	std::regex var("[a-zA-z][a-zA-z0-9]*");
	if (next_token == "config")
	{
		consume("config");
		parse_ConfigStmt();
	}
	else if (next_token == "print")
	{
		consume("print");
		parse_PrintStmt();
	}
	else if (std::regex_match(next_token, var) && peek(1) == "=")
	{
		//Dont consume, variable name is needed in next method.
		parse_AssgStmt();
	}
	else if (next_token[0] == '#' || next_token == "#")
	{
		//Do nothing, this is a comment. Only supports for full comment lines. No support for lines with some code and some comments.
	}
	else if (next_token == "")
	{
		//Do nothing, no code was written on this line and we dont want to throw a runtime error.
	}
	else 
	{
		throw std::runtime_error("Syntax Error: Unexpected token");
	}
}

void Interpreter::parse_ConfigStmt()
{
	std::string next_token = peek();
	if (next_token == "dec")
	{
		consume("dec");
		printType = "dec";
		*outstream << "** Print type set to decimal. **\n";
		*outstream << std::dec;
	}
	else if (next_token == "hex")
	{
		consume("hex");
		printType = "hex";
		*outstream << "** Print type set to hexadecimal. **\n";
		*outstream << std::hex;
	}
	else if (next_token == "bin")
	{
		consume("bin");
		printType = "bin";
		*outstream << "** Print type set to binary. **\n";
	}
	else
	{
		throw std::runtime_error("Unexpected identifier: Expected \'dec\', \'hex\' or \'bin\'");
	}
}

void Interpreter::parse_PrintStmt()
{
	std::string next_token = peek();
	std::regex var("[a-zA-z][a-zA-z0-9]*");
	if (std::regex_match(next_token, var)) { //Next token was a variable
		if (varMap.find(next_token) == varMap.end())
		{
			throw std::runtime_error("Unexpected identifier: Variable with that name could not be found");
		}
		else
		{
			int nbr = varMap.at(next_token);
			if (printType == "dec")
			{
				*outstream << std::dec << nbr << "\n";
			}
			else if (printType == "hex")
			{
				*outstream << "0x" << std::hex << nbr << "\n";
			}
			else if (printType == "bin")
			{
				*outstream << std::bitset<16>(nbr).to_string() << "\n";
			}
			else
			{
				throw std::runtime_error("Print base not set. Set base to print in before printing with the line \"config [dec|hex.|bin]\".");
			}
			consume(next_token);
		}
	}
	else //The next token was a MathExpr
	{
		int nbr = parse_MathExp();
		if (printType == "dec")
		{
			*outstream << std::dec << nbr << "\n";
		}
		else if (printType == "hex")
		{
			*outstream << std::hex << "0x" << nbr << "\n";
		}
		else if (printType == "bin")
		{
			*outstream << std::bitset<16>(nbr).to_string() << "\n";
		}
		else
		{
			throw std::runtime_error("Print base not set. Set base to print in before printing with the line \"config [dec|hex.|bin]\".");
		}
	}
}

void Interpreter::parse_AssgStmt()
{
	std::string varName = peek(); //Store for later use

	//We can consume these as we have saved the important info and we dont need the '='
	consume(varName);
	consume("=");
	int res = parse_MathExp();
	varMap[varName] = res;
}

int Interpreter::parse_MathExp()
{
	return parse_SumExp();
}

int Interpreter::parse_SumExp() //Close to copy pase from F11, zzz
{
	int res = parse_ProductExp();

	std::string next_token = peek();
	while (1)
	{
		if (next_token == "+")
		{
			consume("+");
			int val = parse_ProductExp();
			res = res + val;
		}
		else if (next_token == "-")
		{
			consume("-");
			int val = parse_ProductExp();
			res = res - val;
		}
		else
		{
			break;
		}

		next_token = peek();
	}

	return res;
}

int Interpreter::parse_ProductExp() //Close to copy pase from F11, zzz
{
	int res = parse_PrimaryExp();

	std::string next_token = peek();
	while (1)
	{
		if (next_token == "*")
		{
			consume("*");
			int val = parse_PrimaryExp();
			res = res * val;
		}
		else if (next_token == "/")
		{
			consume("/");
			int val = parse_PrimaryExp();
			res = res / val;
		}
		else
		{
			break;
		}

		next_token = peek();
	}

	return res;
}

int Interpreter::parse_PrimaryExp()
{
	std::string next_token = peek();
	std::regex var("[a-zA-z][a-zA-z0-9]*");
	std::regex nbr("-?[0-9]+");
	
	if (next_token == "(")
	{
		consume("(");
		int val = parse_MathExp();
		consume(")");

		return val;
	}
	else if (std::regex_match(next_token, var)) //Regex matched variable, return value of variable
	{
		if (varMap.find(next_token) != varMap.end())
		{
			consume(next_token);
			return varMap.at(next_token);
		}
		else
		{
			throw std::runtime_error("Variable \"" + next_token + "\" is uninitialized");
		}
	}
	else if (std::regex_match(next_token, nbr)) //Regex matched number
	{
		consume(next_token);
		return stoi(next_token); //stoi convers string to int
	}
	else //Didnt match anything, syntax error
	{
		throw std::runtime_error("Syntax error: expression was not a number or a variable");
	}
}
