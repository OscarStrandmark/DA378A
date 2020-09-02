#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Hello World! Nice to see you, ";
	for (int i = 1; i < argc; i++)
	{
		std::cout << argv[i];

		if (i == argc - 1) //Place space or exclamation mark if end of scentence. 
		{
			std::cout << "!";
		}
		else
		{
			std::cout << " ";
		}
	}
	return 0;
}
