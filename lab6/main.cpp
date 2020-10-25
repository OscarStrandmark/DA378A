#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "Tokenizer.h"
#include "Interpreter.h"

int main()
{

	/*
	Variable for turning on/off debug code. 
	If using an IDE like VS, you can minimize and ignore the if-statements containing this bool as they are usually just print-statements.
	*/
	static bool DEBUGGING = false; 

	//Change path to suit your own installation
	std::string INPUT_FILENAME = "W:/git/DA378A/lab6/code.C@"; 
	std::string OUTPUT_FILENAME = "W:/git/DA378A/lab6/output.txt";

	std::ofstream out (OUTPUT_FILENAME);

	Tokenizer *tokenizer = new Tokenizer();
	Interpreter* interpreter = new Interpreter(out);

	std::ifstream file(INPUT_FILENAME);

	std::vector<std::string> lines; //Contains all the lines from the file

	//Read all lines from the file
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			lines.push_back(line);
		}
		file.close();
	}

	if (DEBUGGING) //Print the lines read from file
	{
		std::cout << std::endl << "LINES READ FROM FILE" << std::endl;
		for (auto s : lines)
		{
			std::cout << s << std::endl;
		}
	}

	//Tokenize! 
	std::vector<std::vector<std::string>> tokenized_lines = tokenizer->tokenize(lines);
	
	if (DEBUGGING)
	{
		std::cout << std::endl << "TOKENIZED STRINGS" << std::endl;
		for (auto I : tokenized_lines)
		{
			for (std::string s : I)
			{
				std::cout << s << ", ";
			}
			std::cout << std::endl;
		}
	}
	
	
	//Now we evaluate each line
	int linecount = 0;
	for (std::vector<std::string> v : tokenized_lines)
	{
		try
		{
			linecount++;
			interpreter->evaluate(v);
			
		}
		catch (std::runtime_error& err)
		{
			out << std::dec; //This is to stop line error was on to be printed in hex. This unfortunately forces some extra std::dec & std::hex statements inside the interpreter
			out << linecount << ": ";
			out << err.what() << std::endl;
		}
	}

	//Delete stuff at the end, because you should.
	delete tokenizer;
	delete interpreter;
	out.close();
}