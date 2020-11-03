#include <iostream>
#include <algorithm>
#include <functional>
#include "tentamen.h"

/*
    --UPPG 3--
    std::vector<int> v = { 14,13,7,4,0,16,9,12,2,19,10,18,5,3,8,1,17,6,11,15 };
    uppg3a(v);
    uppg3b(v);
    uppg3c(v);
    uppg3d(v);
    uppg3e(v);

    --UPPG 4--
    std::function<int(int,int)> addFunc    = add;
    std::function<int(int,int)> addLambda  = [](int a, int b) { return a + b; };
    std::function<int(int, int)> addFunctor = functor();

    std::cout << function_caller(5, 5, addFunc)    << std::endl;
    std::cout << function_caller(5, 5, addLambda)  << std::endl;
    std::cout << function_caller(5, 5, addFunctor) << std::endl;
*/

int main()
{
    PackedIntArray arr = PackedIntArray(15);

    for (size_t i = 0; i < 10; i++)
    {
        arr.insertFast(i, i);
    }
    arr.insertStable(5, 0xA);
    arr.eraseStable(5);
    }

PackedIntArray::PackedIntArray(int capacity)
{
    elements = new int[capacity];
    this->capacity = capacity;
}

PackedIntArray::~PackedIntArray()
{
    delete[] elements;
}

void PackedIntArray::insertFast(int pos, int val)
{
    if (size < capacity)
    {
        elements[pos] = val;
        size++;
    }
}

void PackedIntArray::eraseFast(int pos)
{
    if (pos <= size && pos >= 0) 
    {
        elements[pos] = 0;
        size--;
    }
}

void PackedIntArray::insertStable(int pos, int val)
{
    if (size < capacity)
    {
        for (size_t i = size+1; i > pos; i--)
        {
            elements[i] = elements[i - 1];
        }
        elements[pos] = val;
        size++;
    }
}

void PackedIntArray::eraseStable(int pos)
{
    if (pos <= size && pos >= 0)
    {
        for (size_t i = pos; i <= size; i++)
        {
            elements[i] = elements[i + 1];
        }
        size--;
    }
}

int function_caller(int a, int b, std::function<int(int,int)> func)
{
    return func(a, b);
}

int add(int a, int b)
{
    return a + b;
}

class functor
{
public:
    int operator () (int a, int b) {
        return a + b;
    }
};

void uppg3a(std::vector<int> v) //Even numbers
{
    auto isEven_lmbda = [](int i) { //Capture by reference
        if (i % 2 == 0) {
            return true;
        }
        else
        {
            return false;
        }
    };

    int evenCount = std::count_if(v.begin(), v.end(), isEven_lmbda);

    std::cout << "Size: "                   << v.size()               << std::endl;
    std::cout << "Amount of even numbers: " << evenCount              << std::endl;
    std::cout << "Amount of odd numbers: "  << (v.size() - evenCount) << std::endl;
}

void uppg3b(std::vector<int> v) //Remove odd
{
    auto isOdd_lmbda = [](int i) { //Capture by reference
        if (i % 2 != 0) {
            return true;
        }
    };

    //Returns iterator for all elements to erase
    auto eraseIter = std::remove_if(v.begin(), v.end(), isOdd_lmbda);

    v.erase(eraseIter, v.end());

    for (int i : v) 
    {
        std::cout << i << " ";
    }
}

void uppg3c(std::vector<int> v) //Divide first 5 by 2
{
    for (int i : v) //Print before
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < 5; i++)
    {
        v[i] = v[i] / 2;
    }

    for (int i : v) //Print after
    {
        std::cout << i << " ";
    }
}

void uppg3d(std::vector<int> v)
{
    for (int i : v) //Print before
    {
        std::cout << i << " ";
    }

    //std::swap is cooler
    std::copy(v.begin(), v.begin() + 5, v.rbegin());

    for (int i : v) //Print after
    {
        std::cout << i << " ";
    }
}

void uppg3e(std::vector<int> v)
{
    auto greater_lmbdba = [](int i, int j) {return i > j; };
    std::sort(v.begin(), v.end(),greater_lmbdba);

    for (int i : v) //Print after
    {
        std::cout << i << " ";
    }
}


