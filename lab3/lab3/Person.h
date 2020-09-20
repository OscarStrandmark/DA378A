#pragma once

#include <string>

class Person
{
private:
	std::string name;
	std::string address;
public:
	Person() : name("No name"), address("No address") {} //Default constructor, VS klagar
	Person(std::string name, std::string address);
	virtual ~Person();
	std::string GetName();
	std::string GetAddress();
	virtual void Print();
};