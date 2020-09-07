#include <iostream>
#include <cmath>
#include <string>
#include "Lab2.h";

int main()
{

        //Uppg 1

    //Sieve();

        //Uppg 2

    /*
    std::string iostring = "Hej pa dej";
    std::string before = "ej";
    std::string after = "ig";

    std::cout << "iostring before:\n" << iostring << std::endl;

    substitute_str(iostring, before, after);

    std::cout << "iostring after:\n" << iostring << std::endl;
    */

        //Uppg 3
    char input[] = "Hej pa dej";
    char before = 'j';
    char after[] = "ig";

    std::cout << "input before:\n" << input << std::endl;

    char* output = substitute_cstr(input,before,after);

    std::cout << "output after:\n" << output << std::endl;
}

void Sieve()
{
    int n;

    //Printing & setting n
    std::cout << "Input n" << std::endl;
    std::cin >> n;
    std::cout << n << std::endl;

    int* arr = new int[n];

    for (int i = 0; i < n; i++) //Step 1, fill list with all even numbers bigger than 2.
    {
        arr[i] = i;
    }

    //Handle edge case.
    arr[0] = -1;
    arr[1] = -1;

    for (int i = 0; i < n; i++) //Step 2. Remove all even numbers above 2. 
    {
        if (arr[i] > 2 && arr[i] % 2 == 0) arr[i] = -1;
    }

    for (int i = 0; i < n; i++) //Step 3(1). 
    {
        if (arr[i] != -1) //Step 3(2). Next non-removed number 
        {
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] > arr[i] && arr[j] % arr[i] == 0) //Step 4. Remove all numbers bigger than i 
                {
                    arr[j] = -1;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) //Print numbers
    {
        if (arr[i] != -1) std::cout << arr[i] << " ";
    }

    delete arr;
}

void substitute_str(std::string& iostring, const std::string& before, const std::string& after)
{
    int i = 0;

    while (i != -1 && iostring.size())
    {
        i = iostring.find(before, i);

        if (i != -1)
        {
            iostring.erase(i, before.size());
            iostring.insert(i, after);
            i += after.size();
        }
    }
}

char* substitute_cstr(const char* input, const char before, const char* after)
{
    //Count occurrences of before in input
    int count = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == before) count++;
    }

    //Calculate length of product string
    int l = strlen(input) + (count * strlen(after)) - count;
    char* const returnStr = new char[l+1];

    //Replace all occurrences of before with after.
    for (int i = 0, j = 0; i < l-1; i++)
    {
        if (input[i] == before)
        {
            //before detected, put after in instead.
            for (int k = 0; k < strlen(after); k++) 
            {
                returnStr[j] = after[k];
                j++;
            }
        }
        else //else, continue as normal
        {
            returnStr[j] = input[i];
            j++;
        }
    }

    return returnStr;
}


