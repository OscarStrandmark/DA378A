#include <iostream>
#include "poly2.h"

int main(int argc, char** argv)
{
	std::cout << "Root-finding started..." << std::endl;

    
    bool loop = true;

    while (loop)
    {
        float coef1;
        float coef2;
        float coef3;

        std::cin >> coef1;
        std::cin >> coef2;
        std::cin >> coef3;

        std::cout << "Found polynomial coeffs:" << std::endl;
        std::cout << coef1 << std::endl;
        std::cout << coef2 << std::endl;
        std::cout << coef3 << std::endl;
        std::cout << " " << std::endl;

        Poly2 poly = Poly2(coef1, coef2, coef3);

        int rootCount;
        float rootA;
        float rootB;

        poly.findRoots(rootCount, rootA, rootB);
        if (rootCount > 0)
        {
            std::cout << "Roots found:" << std::endl;
            if (rootCount == 1) {
                std::cout << rootA << std::endl;
                std::cout << "Eval: " << std::endl;
                std::cout << poly.eval(rootA) << std::endl;
            }
            if (rootCount == 2) {
                std::cout << rootA << std::endl;
                std::cout << rootB << std::endl;
                std::cout << "Eval: " << std::endl;
                std::cout << poly.eval(rootA) << std::endl;
                std::cout << poly.eval(rootB) << std::endl;
            }
        }
        else
        {
            std::cout << "No roots found." << std::endl;
        }

        if (std::cin.eof()) loop = false;
    }

    
	return 0;
}