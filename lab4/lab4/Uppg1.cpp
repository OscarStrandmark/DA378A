#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

#include "Uppg1.h"

void u1a()
{
    std::cout << "1a:" << std::endl;

    std::vector<int> v; //Create vector

    //Fill vector with values
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    //Shuffle vector
    std::random_shuffle(v.begin(), v.end());

    //Print vector
    std::cout << "Shuffled vector: ";
    for (auto&& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    //Sort
    std::sort(v.begin(), v.end());

    //Print vector
    std::cout << "Sorted vector:   ";
    for (auto&& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
}

void u1b()
{
    std::cout << "1b:" << std::endl;
    int v[10]; //Create c-arr

    std::iota(&v[0], &v[10], 0); //Fill randomly. Why &v[10] and not &v[9]? Is it not including the last index?
    std::random_shuffle(std::begin(v), std::end(v)); //Shuffle c-arr

    //Print c-arr
    std::cout << "Shuffled c-arr: ";
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::sort(std::begin(v), std::end(v)); //Sort c-arr

    //Print c-arr
    std::cout << "Sorted c-arr:   ";
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl; //Padding
}

void u1c()
{
    std::cout << "1c:" << std::endl;

    std::vector<int> v; //Create vector

    //Fill vector with values
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    //Shuffle vector
    std::random_shuffle(v.begin(), v.end());

    //Print vector
    std::cout << "Shuffled vector: ";
    for (auto&& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    //Sort backwards
    std::sort(v.rbegin(), v.rend());

    //Print vector
    std::cout << "Sorted vector:   ";
    for (auto&& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
}

void u1d()
{
    std::cout << "1d:" << std::endl;
    int v[10]; //Create c-arr

    std::iota(&v[0], &v[10], 0); //Fill randomly. Why &v[10]? End-index is excluded, see image: https://i.stack.imgur.com/oa3EQ.png
    std::random_shuffle(std::begin(v), std::end(v)); //Shuffle c-arr

    //Print c-arr
    std::cout << "Shuffled c-arr: ";
    for (int i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::sort(std::begin(v), std::end(v), greater); //Sort c-arr

    //Print c-arr
    std::cout << "Sorted c-arr:   ";
    for (auto i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl; //Padding
}

bool greater(int x, int y)
{
    return x > y;
}