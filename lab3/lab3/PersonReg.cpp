#include "PersonReg.h"
#include <iostream>

Person* personer;
int maxSize;
int currentSize;


PersonReg::PersonReg(int maxSize) //Constructor
{
	this->maxSize = maxSize;
	this->currentSize = 0;

	//Allocate the memory 
	personer = new Person[maxSize];
}

PersonReg::~PersonReg() //Deconstructor
{
	delete[] personer;
}


void PersonReg::AddPerson(Person* person)
{
	personer[currentSize] = *person;
	currentSize++;
}

void PersonReg::RemovePerson(Person* person)
{
	//Pointer for seeing if person was found
	Person* retPerson = nullptr;

	//Vars for cleaner code
	int nameComp = -1;
	int addressComp = -1;

	//Var for finding where to start when cleaning list
	int i = 0;

	//Iterate over all persons
	for (Person* ptr = personer; ptr != personer + currentSize; ++ptr)
	{
		//Do comparisons.
		nameComp = ptr->GetName().compare(person->GetName());
		addressComp = ptr->GetAddress().compare(person->GetAddress());
		if (nameComp == 0 && addressComp == 0)
		{
			//If found matching person, get that person and stop iterating.
			retPerson = ptr;
			break;
		}
		i++;
	}

	if (retPerson)
	{
		//Push all persons in higher indexes to one index lower to fill the empty index. 
		for (int j = i; j < currentSize; j++)
		{
			personer[j] = personer[j + 1];
		}
		currentSize--; //Reduce amount of persons in register by 1.
	}
	else
	{
		//If no person was found, print error message. 
		std::cout << "Could not find person with that name and address." << std::endl;
	}
}

Person* PersonReg::SearchPersonName(std::string name)
{
	for (Person* ptr = personer; ptr != personer + currentSize; ++ptr)
	{
		if ((ptr->GetName()).compare(name) == 0)
		{
			return ptr;
		}
	}

	return nullptr;
}

Person* PersonReg::SearchKeyword(std::string keyword, Person* from)
{
	if (from == nullptr) //if from is nullptr, start from beginning of register
	{
		from = personer;
	}
	else //if from is not nullpointer, start searching after its index. 
	{
		from = (from + 1);
	}

	//Loop until undefined person name. 
	for (Person* ptr = from; (ptr->GetName()).compare(std::string("No name")) != 0; ++ptr)
	{
		//If keyword is name or address. 
		if ((ptr->GetName()).find(keyword, 0) != -1 || (ptr->GetAddress()).find(keyword, 0) != -1) {
			return ptr;
		}
	}

	//If not found, return nullptr
	return nullptr;
}


void PersonReg::PrintRegister()
{
	for (Person* ptr = personer; ptr != personer + currentSize; ++ptr) 
	{
		ptr->Print();
	}
}