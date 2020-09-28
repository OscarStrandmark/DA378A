#include "Person.h"
#include "PersonReg.h"
#include <iostream>
#include <algorithm>

void u2a()
{
	std::cout << "2a: " << std::endl;

	PersonReg* reg = new PersonReg(10);
	reg->AddPerson(&Person("AA", "A-Gatan"));
	reg->AddPerson(&Person("AA", "B-Gatan"));
	reg->AddPerson(&Person("AE", "C-Gatan"));
	reg->AddPerson(&Person("AB", "D-Gatan"));
	reg->AddPerson(&Person("AC", "E-Gatan"));
	reg->AddPerson(&Person("AD", "F-Gatan"));

	std::cout << "Shuffled register: " << std::endl;
	std::random_shuffle(reg->begin(), reg->end());

	reg->PrintRegister();

	std::sort(reg->begin(), reg->end());
	
	std::cout << "Sorted register: " << std::endl;
	reg->PrintRegister();

	delete reg;

	std::cout << std::endl;
}

void u2b()
{
	std::cout << "2a: " << std::endl;

	PersonReg* reg = new PersonReg(10);
	reg->AddPerson(&Person("AA", "A-Gatan"));
	reg->AddPerson(&Person("AA", "B-Gatan"));
	reg->AddPerson(&Person("AE", "C-Gatan"));
	reg->AddPerson(&Person("AB", "D-Gatan"));
	reg->AddPerson(&Person("AC", "E-Gatan"));
	reg->AddPerson(&Person("AD", "F-Gatan"));

	std::random_shuffle(reg->begin(), reg->end());

	std::cout << "Shuffled register: " << std::endl;
	reg->PrintRegister();

	std::sort(reg->begin(), reg->end());

	std::cout << "Sorted register: " << std::endl;
	reg->PrintRegister();

	delete reg;

	std::cout << std::endl;
}