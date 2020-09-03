#include "poly2.h"
#include <iostream>
#include <cmath>

Poly2::Poly2(float a, float b, float c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

float Poly2::eval(float x)
{
    float val = (a * x * x) + (b * x) + c;
    return val;
}

void Poly2::findRoots(int &rootCount, float &rootA, float &rootB)
{
    float d = pow(b,2) - (4 * a * c);
    if (d < 0)
    {
        /*
        * Uppg 8
        * std::cout << "2 imaginary roots";
        * std::cout << "" << std::endl;
        */
        
        rootCount = 0;

    }
    else if (d == 0)
    {
        float root0 = (b * -1) / (2 * a);

        /*
        * Uppg 8
        * std::cout << "One real root:" << std::endl;
        * std::cout << root0 << std::endl;
        * std::cout << "" << std::endl;
        */

        rootCount = 1;
        rootA = root0;

    }
    else if (d > 0)
    {
        
        float plmi = sqrt(pow(b,2) - (4 * a * c));
        float root1 = ((b * -1) + plmi) / (2 * a);
        float root2 = ((b * -1) - plmi) / (2 * a);
        
        /*
        * Uppg 8
        * std::cout << "Two real roots:" << std::endl;
        * std::cout << root1 << std::endl;
        * std::cout << root2 << std::endl;
        * std::cout << "" << std::endl;
        */

        rootCount = 2;
        rootA = root1;
        rootB = root2;
    }

}


int main() {

    /*
    
    Denna kod tillhör uppgift 9 & 8

    Poly2 polyA = Poly2(1, 2, 1);
    Poly2 polyB = Poly2(2, -1, -1);
    Poly2 polyC = Poly2(1, 1, 1);

    std::cout << polyA.eval(-1) << std::endl;
    std::cout << polyB.eval(4) << std::endl;
    std::cout << polyC.eval(4) << std::endl;

    int rootCount;
    float rootA;
    float rootB;

    polyA.findRoots(rootCount, rootA, rootB);
    
    std::cout << "Roots found: " << rootCount << std::endl;
    if (rootCount > 0) 
    {
        if (rootCount == 1) {
            std::cout << rootA << std::endl;
            std::cout << polyA.eval(rootA) << std::endl;
        }
        if (rootCount == 2) {
            std::cout << rootA << std::endl;
            std::cout << rootB << std::endl;
            std::cout << polyA.eval(rootA) << std::endl;
            std::cout << polyA.eval(rootB) << std::endl;
        }
    }
    
    polyB.findRoots(rootCount, rootA, rootB);

    std::cout << "Roots found: " << rootCount << std::endl;
    if (rootCount > 0)
    {
        if (rootCount == 1) {
            std::cout << rootA << std::endl;
            std::cout << polyB.eval(rootA) << std::endl;
        }
        if (rootCount == 2) {
            std::cout << rootA << std::endl;
            std::cout << rootB << std::endl;
            std::cout << polyB.eval(rootA) << std::endl;
            std::cout << polyB.eval(rootB) << std::endl;
        }
    }

    polyC.findRoots(rootCount, rootA, rootB);

    std::cout << "Roots found: " << rootCount << std::endl;
    if (rootCount > 0)
    {
        if (rootCount == 1) {
            std::cout << rootA << std::endl;
            std::cout << polyC.eval(rootA) << std::endl;
        }
        if (rootCount == 2) {
            std::cout << rootA << std::endl;
            std::cout << rootB << std::endl;
            std::cout << polyC.eval(rootA) << std::endl;
            std::cout << polyC.eval(rootB) << std::endl;
        }
    }
    */

    //Uppgift 10:

    float coefA;
    float coefB;
    float coefC;

    while (1)
    {
        std::cout << "Mata in 3 tal." << std::endl;
        //Read coeffs
        std::cin >> coefA;
        std::cin >> coefB;
        std::cin >> coefC;

        //Calc roots
        Poly2 polynom = Poly2(coefA, coefB, coefC);
        int rootCount;
        float rootA;
        float rootB;
        polynom.findRoots(rootCount, rootA, rootB);
        std::cout << "Roots found: " << rootCount << std::endl;
        if (rootCount > 0)
        {
            if (rootCount == 1) {
                std::cout << rootA << std::endl;
                std::cout << std::endl;
            }
            if (rootCount == 2) {
                std::cout << rootA << std::endl;
                std::cout << rootB << std::endl;
                std::cout << std::endl;
            }
        }

        //Again?
        char c;
        std::cout << "Vill du forts. skapa polynom? y/n" << std::endl;
        std::cin >> c;
        if (c != 'y') {
            break;
        }
    }

   

   
}


