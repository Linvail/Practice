// ValidPalindrome.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    //! Idea: scan from left and right. -->     <---
    //! 
    static bool isPalindrome( const string& s )
    {
        const size_t stringLen = s.length();
        if( stringLen <= 1 )
        {
            return true;
        }

        size_t leftIdx = 0;
        size_t rightIdx = stringLen - 1;
        bool result = true;

        while( leftIdx < rightIdx )
        {
            while( !isAlphaumeric( s[leftIdx] ) && leftIdx < rightIdx )
            {
                leftIdx++;
            }

            while( !isAlphaumeric( s[rightIdx] ) && rightIdx > leftIdx )
            {
                rightIdx--;
            }

            if( leftIdx >= rightIdx )
            {
                break;
            }

            if( !isEqual( s[leftIdx], s[rightIdx] ) )
            {
                result = false;
                break;
            }

            leftIdx++;
            rightIdx--;
        }


        return result;
    }

    inline static bool isAlphaumeric( char aCharacter )
    {
        if( ( aCharacter >= 'a' && aCharacter <= 'z' ) ||
            ( aCharacter >= 'A' && aCharacter <= 'Z' ) ||
            ( aCharacter >= '0' && aCharacter <= '9' ) )
        {
            return true;
        }

        return false;
    }

    inline static bool isEqual( char aCharLeft, char aCharRight )
    {
        // Covert character to lower.
        if( aCharLeft >= 'A' && aCharLeft <= 'Z' )
        {
            aCharLeft = 'a' + aCharLeft - 'A';
        }
        if( aCharRight >= 'A' && aCharRight <= 'Z' )
        {
            aCharRight = 'a' + aCharRight - 'A';
        }

        return aCharLeft == aCharRight;
    }

};

int main()
{
    string testData( "A man, a plan, a canal: Panama" );

    std::cout << "ValidPalindrome: " << Solution::isPalindrome( testData )  << "\n";

    testData = "race a car";

    std::cout << "ValidPalindrome: " << Solution::isPalindrome( testData ) << "\n";

    testData = " ";

    std::cout << "ValidPalindrome: " << Solution::isPalindrome( testData ) << "\n";
}
