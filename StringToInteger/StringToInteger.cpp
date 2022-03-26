// StringToInteger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
    static int myAtoi( string s )
    {
        if( s.length() == 0 )
        {
            return 0;
        }

        size_t i = 0;
        for( ; i < s.length(); ++i )
        {
            if( s[i] != ' ' )
            {
                break;
            }
        }

        bool negative = false;
        if( s[i] == '-' )
        {
            negative = true;
            i++;
        }
        else if( s[i] == '+' )
        {
            i++;
        }

        int result = 0;
        for( ; i < s.length(); ++i )
        {
            if( !( s[i] >= '0' && s[i] <= '9' ) )
            {
                break;
            }
            else
            {
                if( negative )
                {
                    // INT_MIN is -2147483648.
                    if( result > ( INT_MIN / -10 ) )
                    {
                        result = INT_MIN;
                        negative = false;
                        break;
                    }
                    else if( result == ( INT_MIN / -10 ) )
                    {
                        if( s[i] - '0' >= 8 )
                        {
                            result = INT_MIN;
                            negative = false;
                            break;
                        }
                    }                    
                }
                else
                {
                    // INT_MAX is 2147483647
                    if( result > INT_MAX / 10 )
                    {
                        result = INT_MAX;
                        break;
                    }
                    else if( result == INT_MAX / 10 )
                    {
                        if( s[i] - '0' >= 7 )
                        {
                            result = INT_MAX;
                            break;
                        }
                    }
                }
                
                result *= 10;
                result += s[i] - '0';
            }
        }
        return negative ? -result : result;
    }
};

int main()
{
    string testData( "42" );
    std::cout << "StringToInteger: " << Solution::myAtoi( testData ) << "\n";

    testData = "   -42";
    std::cout << "StringToInteger: " << Solution::myAtoi( testData ) << "\n";

    testData = "4193 with words";
    std::cout << "StringToInteger: " << Solution::myAtoi( testData ) << "\n";

    testData = "+1";
    std::cout << "StringToInteger: " << Solution::myAtoi( testData ) << "\n";

    // 2147483647 + 1
    testData = "2147483648";
    std::cout << "StringToInteger: " << Solution::myAtoi( testData ) << "\n";

    // -2147483648 - 1
    testData = "-2147483649";
    std::cout << "StringToInteger: " << Solution::myAtoi( testData ) << "\n";

    testData = "-91283472332";
    std::cout << "StringToInteger: " << Solution::myAtoi( testData ) << "\n";
}

