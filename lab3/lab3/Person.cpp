#include "Person.h"

#include <iostream>
#include <string>

std::string name;
std::string address;

Person::Person(std::string name, std::string address)
{
	this->name = name;
	this->address = address;
}

Person::~Person()
{

}

std::string Person::GetName()
{
	return name;
}

std::string Person::GetAddress()
{
	return address;
}
void Person::Print()
{
	//Print name and address. 
	std::cout << name << " " << address << std::endl;
}

bool Person::operator<(const Person& that)
{
	return this->name > that.name;
}
