#include "String.h"
#include <string.h>

char* str = nullptr;
int cap = 1;
int siz = 0;

/*
##########################################################
############### CONSTRUCTORS & DESTRUCTORS ###############
##########################################################
*/

String::~String()
{
	if (str) //Check if string isnt nullptr, wouldn't need to delete if it was never created
	{
		Invariant();
		delete[] str;
	}
}

String::String()
{
	String("");
}

String::String(const String& rhs)
{
	*this = rhs; //rhs should already exist on the Heap
	Invariant();
}

String::String(const char* cstr)
{
	cap = strlen(cstr); //Get length of arg char*
	siz = 0;
	str = new char[cap]; //Set that length as the capacity of this

	int i = 0;
	while (cstr[i] != '\0') //Loop through all chars in arg char*
	{
		push_back(cstr[i]); //Append char to end of String
		i++;
	}
	Invariant();
}

/*
##########################################################
#################### PUBLIC FUNCTIONS ####################
##########################################################
*/

size_t String::size() const
{
	return siz;
}

size_t String::capacity() const
{
	return cap;
}

void String::push_back(char c)
{
	//Before appending, check if there is enough memory. If not, double the size. 
	if (size() == 0) AllocateNewMemory(1);
	else if (siz >= (int)capacity()) AllocateNewMemory(cap * 2); 

	str[siz++] = c;
	
}

const char* String::data() const
{
	return str;
}


/*
##########################################################
######################## OPERATORS #######################
##########################################################
*/


String& String::operator = (const String& rhs)
{
	if (&rhs != this) //do not run code if attempting to declare to itself. 
	{
		if (rhs.size() == size())
		{
			//copy over char values
			for (int i = 0; i < siz; i++)
			{
				str[i] = rhs[i];
			}
		}
		else
		{
			if (str) delete[] str; //If it exists, delete

						//Copy over size, capacity and string length.
			siz = rhs.size();
			cap = rhs.capacity();
			str = new char[cap];

			//copy over char values
			for (int i = 0; i < siz; i++)
			{
				str[i] = rhs[i];
			}
		}
	}
	return *this; //Deref to return yourself.
}

char& String::operator[](size_t i)
{
	return str[i];
}

const char& String::operator[](size_t i) const
{
	return str[i];
}

bool operator==(const String& lhs, const String& rhs)
{
	return std::equal(lhs.str, lhs.str + lhs.size(), rhs.str);
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(std::equal(lhs.str, lhs.str + lhs.size(), rhs.str));
}

std::ostream& operator<<(std::ostream& out, const String& rhs)
{
	for (int i = 0; i < rhs.size(); i++)
	{
		out << rhs[i];
	}
	return out;
}

/*
##########################################################
################### PRIVATE FUNCTIONS ####################
##########################################################
*/

void String::Invariant()
{
	assert(siz <= cap); //idk
}

void String::AllocateNewMemory(int size)
{
	cap = size;

	//Allocate the new memory
	char* temp = new char[cap];

	//Copy chars to temp storage
	for (int i = 0; i < siz; i++)
	{
		temp[i] = str[i];
	}
	
	//Delete if it exists
	if (str) delete[] str;

	//Allocate new memory
	str = new char[cap];

	for (int i = 0; i < siz; i++)
	{
		str[i] = temp[i];
	}

	delete[] temp;
}