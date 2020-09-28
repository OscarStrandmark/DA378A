#include "Person.h"

class PersonReg
{
private:
	Person* personer;
	int maxSize;
	int currentSize;

public:
	PersonReg(int maxSize);
	void AddPerson(Person* person);
	void RemovePerson(Person* person);
	Person* SearchPersonName(std::string name);
	Person* SearchKeyword(std::string keyword, Person* from);
	void PrintRegister();
	~PersonReg();
	Person* begin();
	Person* end();
};