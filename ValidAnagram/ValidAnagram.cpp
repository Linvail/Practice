// ValidAnagram.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    //! Asume s and t consist of lowercase English letters.
    static bool isAnagram( string s, string t )
    {
        if( s.length() != t.length() )
        {
            return false;
        }

        vector<int> charTableS( 26, 0 );
        vector<int> charTableT( 26, 0 );

        for( int i = 0; i < s.length(); ++i )
        {
            charTableS[s[i] - 'a']++;
            charTableT[t[i] - 'a']++;
        }

        return charTableS == charTableT;
    }

    // Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
    // Solution: 1. sort and comare. 2. using hash - std::map<char, int>.
};

int main()
{
    string s( "anagram" );
    string t( "nagaram" );

    std::cout << "Valid anagram: " << Solution::isAnagram( s, t ) <<  "\n";

    s = "abc";
    t = "efg";

    std::cout << "Valid anagram: " << Solution::isAnagram( s, t ) << "\n";
}
