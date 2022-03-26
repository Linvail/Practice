// FirstUniqueCharacter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    static int firstUniqChar( string s )
    {
        vector<int> allowedChar(26, -1);
        int index = 0;
        for( char c : s )
        {
            if( allowedChar[c - 'a'] == -1 )
            {
                allowedChar[c - 'a'] = index;
            }
            else if( allowedChar[c - 'a'] >= 0 )
            {
                allowedChar[c - 'a'] = -2;
            }

            index++;
        }

        index = -1;

        int min = s.length();
        for( int i = 0; i < 26; ++i )
        {
            if( allowedChar[i] >= 0 && allowedChar[i] < min )
            {
                min = allowedChar[i];
            }
        }

        return min == s.length() ? -1 : min;
    }
};

int main()
{
   
    string testData( "loveleetcode" );

    std::cout << "firstUniqChar: " << Solution::firstUniqChar( testData  ) << "\n";

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
