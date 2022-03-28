// LongestCommonPrefix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    static string longestCommonPrefix( vector<string>& strs )
    {
        if( strs.size() == 0 )
        {
            return "";
        }
        else if( strs.size() == 1 )
        {
            return strs[0];
        }

        bool end = false;

        size_t i = 0;
        for( ; i < strs[0].length() && !end; ++i )
        {
            for( size_t j = 1; j < strs.size(); ++j )
            {
                if( i >= strs[j].length() || strs[0][i] != strs[j][i] )
                {
                    end = true;
                    break;
                }
            }
        }

        return strs[0].substr( 0, end ? i - 1 : i );
    }

    static string longestCommonPrefix2( vector<string>& strs )
    {
        if( strs.size() == 0 )
        {
            return "";
        }

        string& matchedStr = strs[0];

        for( size_t j = 1; j < strs.size(); ++j )
        {
            size_t i = 0;
            for( ; i < matchedStr.length() && i < strs[j].length(); ++i )
            {
                if( matchedStr[i] != strs[j][i] )
                {
                    break;
                }
            }

            matchedStr.erase( i, matchedStr.length() );
        }

        return matchedStr;
    }
};

int main()
{
    vector<string> testData{ "flower", "flow", "flight", "fl" };
    std::cout << "LongestCommonPrefix: " << Solution::longestCommonPrefix( testData ) << endl;

    vector<string> testData2{ "flower", "flower", "flower", "flower" };
    //vector<string> testData2{ "flower", "flow", "flight", "fl" };
    std::cout << "LongestCommonPrefix: " << Solution::longestCommonPrefix( testData2 ) << endl;
}
