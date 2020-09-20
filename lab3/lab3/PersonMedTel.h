#pragma once

#include "Person.h"


class PersonMedTel : public Person {
private:
	std::string tel;
public:
	PersonMedTel() : Person(),tel("No number") {}
	PersonMedTel(std::string name, std::string address, std::string tel) : Person(name,address), tel(tel) {}
	std::string GetTel();
	void Print();
};