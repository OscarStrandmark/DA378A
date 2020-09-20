#include "PersonMedTel.h"
#include "Person.h"

#include <string>
#include <iostream>

std::string tel;

std::string PersonMedTel::GetTel()
{
	return tel;
}

void PersonMedTel::Print()
{
	std::cout << Person::GetName() << " " << Person::GetAddress() << " " << tel << std::endl;
}