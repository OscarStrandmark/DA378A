#include "PersonReg.h"
#include "PersonMedTel.h"
#include <fstream>
#include <iostream>
#ifdef _DEBUG
#ifndef DBG_NEW
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

bool readReg(PersonReg& reg, std::string filename)
{
	std::string line;
	std::ifstream myfile(filename);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			while (line.length() == 0 && getline(myfile, line));
			std::string name(line);
			std::string address;
			getline(myfile, address);
			reg.AddPerson(&Person(name, address));
		}
		myfile.close();
		return true;
	}
	else
	{
		std::cout << "Unable to open file";
		return false;
	}
}

int main()
{
#ifdef DBG_NEW
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	std::locale::global(std::locale("swedish"));

	//Create register
	PersonReg* reg = new PersonReg(16);

	//Add person to register
	Person* pers = new Person("Sven Svensson", "Svenssongatan 4A, 21619 MALM�");
	reg->AddPerson(pers);

	//Read from file
	std::string filename = "W:/git/DA378A/lab3/lab3/PersonExempel.txt"; //ATTN CHANGE THIS IF YOU NEED IT 
	readReg(*reg, filename);

	//Print register
	std::cout << "Register:" << std::endl << "-----" << std::endl;
	reg->PrintRegister();

	//Remove person from register
	std::cout << std::endl << "Person removed from register." << std::endl;
	reg->RemovePerson(pers);

	//Print register
	std::cout << std::endl << "Register:" << std::endl << "-----" << std::endl;
	reg->PrintRegister();

	//Search name
	std::string name = "Nicklas Mattsson";
	std::cout << std::endl << "Search by name: " << name << std::endl << "-----" << std::endl;
	Person* p1 = reg->SearchPersonName(name);

	if (p1) p1->Print(); //Print if not nullptr. 

	//Search by keyword
	std::string keyword = "tr�sk";
	std::cout << std::endl << "Search by keyword: " << keyword << std::endl << "-----" << std::endl;
	Person* p2 = reg->SearchKeyword(keyword,nullptr);

	if (p2) p2->Print(); //Print if not nullptr. 

	//Print with telephone nbr
	Person* telPerson = new PersonMedTel("Samuel Samuelsson", "Samuelsgatan 24 21612 MALM�", "1234567890");
	std::cout << std::endl << "Print with telephone number: "  << std::endl << "-----" << std::endl;
	telPerson->Print();

	//Print with telephone nbr while in register
	reg->AddPerson(telPerson);
	std::cout << std::endl << "Print register with person with telephone number: " << std::endl << "-----" << std::endl;
	reg->PrintRegister();

	std::cout << std::endl << "Enter to close";
	std::getchar();

	//Delete shit, 
	delete telPerson;
	delete pers;
	delete reg;

	_CrtDumpMemoryLeaks();
	return 0;
}