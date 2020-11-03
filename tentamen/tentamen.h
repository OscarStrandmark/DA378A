#pragma once
#include <vector>

int main();
void uppg3a(std::vector<int> v);
void uppg3b(std::vector<int> v);
void uppg3c(std::vector<int> v);
void uppg3d(std::vector<int> v);

int function_caller(int a, int b, std::function<int(int, int)> func);
int add(int a, int b);

class PackedIntArray
{
#include <algorithm>
private:
	int* elements;
	int capacity = 0;
	int size = 0;

public:

	PackedIntArray(int capacity);
	~PackedIntArray();

	void insertFast(int pos, int val);
	void eraseFast(int pos);
	void insertStable(int pos, int val);
	void eraseStable(int pos);
};