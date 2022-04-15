// main.cpp : Defines the entry point for the console application.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Cpp14Features.h"

using namespace std;

int main()
{
    //////////////////////////////////////////////////////////////////////////////////////////////
    Cpp14Features::test_lambda();

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Try to use decltype.
    int i = 1;
    double x = 3;
    decltype( x + i * 2 ) y = 5.5; // y 是 double，因為 x+i*2 會自動把 int cast 成 double
    std::cout << y << std::endl;
    cout << endl;

    //////////////////////////////////////////////////////////////////////////////////////////////

    Cpp14Features::test_forward();

    cout << endl;

    Cpp14Features::test_move();
}