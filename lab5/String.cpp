#include "String.h"

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
	size = capacity = strlen(cstr); //Get length of arg char*
	str = new char[capacity]; //Set that length as the capacity of this

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
	return size;
}

size_t String::capacity() const
{
	return capacity;
}

void String::push_back(char c)
{
	//Before appending, check if there is enough memory. If not, double the size. 
	if (size() == 0) AllocateNewMemory(1);
	else if (size >= capacity()) AllocateNewMemory(capacity * 2); 

	str[n++] = c;
	
}

const char* String::data() const
{
	return nullptr;
}


/*
##########################################################
######################## OPERATORS #######################
##########################################################
*/


String& String::operator = (const String& rhs)
{
	if (str) delete[] str; //If it exists, delete

	//Copy over size, capacity and string length.
	size = rhs.size();
	capacity = rhs.capacity();
	str = new char[capacity];
	
	//copy over char values
	for (int i = 0; i < size; i++)
	{
		str[i] = rhs[i];
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
	return !(lhs == rhs));
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
	assert(size <= capacity); //idk
}

void String::AllocateNewMemory(int size)
{

}


