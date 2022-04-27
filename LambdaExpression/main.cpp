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
    decltype( x + i * 2 ) y = 5.5; // y �O double�A�]�� x+i*2 �|�۰ʧ� int cast �� double
    std::cout << y << std::endl;
    cout << endl;

    //////////////////////////////////////////////////////////////////////////////////////////////

    Cpp14Features::test_forward();

    cout << endl;

    Cpp14Features::test_move();
}