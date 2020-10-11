#pragma once
#include <cassert>
#include <iostream>
#include <algorithm>

class String
{
private:
	//Vars
	char* str = nullptr;
	int cap = 1;
	int siz = 0;

	//Private Funcs
	void Invariant();
	void AllocateNewMemory(int size);
public:
	//Constructors & Desctuctors
	String();
	String(const String& rhs);
	String(const char* cstr);
	~String();

	//Funcs
	size_t size() const;
	size_t capacity() const;
	void push_back(char c);
	const char* data() const;

	//Operators
	String& operator=(const String& rhs);
	char& operator[](size_t i);
	const char& operator[](size_t i) const;
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator != (const String& lhs, const String& rhs);
	friend std::ostream& operator<< (std::ostream& out, const String& rhs);
};