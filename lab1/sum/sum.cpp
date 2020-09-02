#include <iostream>	

int main() {
	short val;
	short sum = 0;
	std::cout << "Enter numbers to add." << std::endl;
	while (std::cin >> val)
	{
		sum = sum + val;
	}
	std::cout << sum << std::endl;
}
