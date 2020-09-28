#include "Uppg3.h"
#include <iostream>
#include <algorithm>
#include <vector>

void u3()
{
	std::cout << "u3:" << std::endl;
	std::vector<int> v; //Create vector
	for (int i = 0; i < 10; i++) //Fill with values
	{
		v.push_back(i);
	}

	//Shuffle vector
	//std::random_shuffle(v.begin(), v.end());

	//Print
	std::cout << "Shuffled vector" << std::endl;
	for (auto i : v)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	//remove-if moves all the even numbers to one side of the vector and returns the position of where the even number start. 
	//Erase then removes all the numbers from the returned index to the end of the vector. 
	v.erase(std::remove_if(v.begin(), v.end(), Even),v.end());

	//Print
	std::cout << "erased vector" << std::endl;
	for (auto i : v)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

bool Even(int i)
{
	return i % 2 == 0;
}