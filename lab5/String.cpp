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
	//Changed accordingly to comment on turnin that nullptr is better than initializing an empty string as it still reserves memory if its empty.
	//String(""); 
	str = nullptr;
	siz = 0;
	cap = 0;
}

String::String(const String& rhs)
{
	//Changed according to comment on turnin that I should not call operator= with uninitialized memory on the left side (*this)
	//*this = rhs;

	cap = rhs.capacity();
	siz = rhs.size();
	str = new char[cap];

	for (size_t i = 0; i < siz; i++)
	{
		str[i] = rhs[i];
	}

	Invariant();
}

String::String(const char* cstr)
{
	cap = strlen(cstr); //Get length of arg char*
	std::cout << cap << std::endl;
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
	if (capacity() == 0) AllocateNewMemory(1);
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
	/*
	* Three difference scenarios can happen here that we care about:
	* rhs.size > capacity
	* rhs.size = capacity
	* rhs.size < capacity
	* Two of these are handled the same way (= and >, since in both scenarios the allocated memory has space for the rhs content.)
	*/
	if (&rhs != this) //do not run code if attempting to declare to itself. 
	{
		if (rhs.size() > capacity())
		{
			delete[] str; //If it exists, delete

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
		else if (rhs.size() == capacity() || rhs.size() < capacity()) //handled the same
		{	

			for (int i = 0; i < capacity(); i++)
			{
				str[i] = rhs[i]; //Copy over contents of rhs.
			}

			siz = rhs.size();
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
	if (lhs.size() == rhs.size()) //For lhs and rhs to be equal, size has to be the same.
	{
		for (size_t i = 0; i < lhs.size(); i++) //lhs.size == rhs.size, no unallocated memory should never be accessed. 
		{
			if (lhs[i] != rhs[i]) //Check if letters are not matching
			{
				return false; //If found not matching letters
			}
		}
		return true; //If all letters matched, strings are equal. Return true
	}
	return false;

	//Old code did not work with new testcode. 
	//return std::equal(lhs.str, lhs.str + lhs.size(), rhs.str); 
}

bool operator!=(const String& lhs, const String& rhs)
{
	return ! (lhs == rhs);
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