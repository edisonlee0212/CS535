// CS535.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math.h"
using namespace CS535;
int main()
{
    std::cout << "Hello World!\n";

    vec3 v1(1, 2, 3);
    vec3 v2(1, 0, 0);
    vec3 v3 = v1 / 2.0f;
    mat4 m;
    m = Translate(mat4::Identity(), v3);
    std::cout << m << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
