// ImplementStrStr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    static int strStr( string haystack, string needle )
    {
        if( needle.length() == 0 )
        {
            return 0;
        }

        if( needle.length() > haystack.length() )
        {
            return -1;
        }

        int result = -1;
        for( int i = 0; i < haystack.length(); ++i )
        {
            if( haystack[i] == needle[0] )
            {
                /*int j = 0;
                for( ; j < needle.length(); ++j )
                {
                    if( haystack[i + j] != needle[j] )
                    {
                        break;
                    }
                }
                if( j == needle.length() )
                {
                    result = i;
                    break;
                }*/
                if( 0 == haystack.compare( i, needle.length(), needle ) )
                {
                    result = i;
                    break;
                }
            }
        }

        return result;
    }

    //!  lps[i] = the longest proper prefix of pattern[0..i] which is also a suffix of pattern[0..i].
    /* 
    for text = ¡§pqprpqps¡¨
    LPS[0] = 0 ( because length of proper prefix of any single character string is always 0 )
    LPS[1] = 0 ( for ¡§pq¡¨ there is no prefix which is also a suffix. )
    LPS[2] = 1 ( for ¡§pqp¡¨ longest prefix which is also a suffix = ¡¨p¡¨ )
    LPS[3] = 0 ( for ¡§pqpr¡¨ there is no prefix which is also a suffix )
    LPS[4] = 1 ( for ¡§pqprp¡¨ longest prefix which is also a suffix = ¡¨p¡¨ )
    LPS[5] = 2 ( for ¡§pqprpq¡¨ longest prefix which is also a suffix = ¡¨pq¡¨ )
    LPS[6] = 3 ( for ¡§pqprpqp¡¨ longest prefix which is also a suffix = ¡¨pqp¡¨ )
    LPS[7] = 0 ( for ¡§pqprpqps¡¨ there is no prefix which is also a suffix )
    */
    static void buildLps( const string& aPattern, vector<int>& aLps )
    {
        int len = 0;
        int i = 1;
        aLps[0] = 0;

        while( i < aPattern.length() )
        {
            if( aPattern[i] == aPattern[len] )
            {
                len++;
                aLps[i] = len;
                i++;
                continue;
            }
            else
            {
                if( len == 0 )
                {
                    aLps[i] = 0;
                    i++;
                }
                else
                {
                    // This is tricky.
                    // Consider we previously got pqp-r-pqp, len = 3, i = 6.
                    // In the next loop, now we get pqp-r-pqp-s, len = 3, i = 7. 'r' != 's'.
                    // We know the 4th char is not equal to the last one.
                    // aLps[len - 1] means the lps of the latest matched sub-pattern (length is 3. pqp).                    
                    len = aLps[len - 1];
                    // Ater we upated len, len becomes 1, meaning we are going to compare 'q' with 's'.
                    // 
                    // The reason why we update len in this way is that we want to save unnecessary comparisons (we don't want to start with 0).
                    // Here, len is not 0, meaning there is a sub-pattern (pqp) just before 's', and the same sub-pattern is located in the front (starts with 0).
                    // len is 1. It means that in the sub-pattern (pqp), the 1st and last char is the same.
                    // So we can know:
                    // 1. In the front sub-pattern, aPattern[0] == aPattern[2].
                    // 2. In the back sub-patteren, aPattern[4] == aPattern[6].
                    // So, we can know aPattern[0] == aPattern[6]. The current i is 7, so we should compare aPattern[1] with aPattern[7].
                    // 
                    // Note that we don't increment i here.
                }
            }
        }

        // print out...
        /*
        cout << "LPS of " << aPattern << " is: " << "\n";        
        for( i = 0; i < aLps.size(); ++i )
        {
            cout << "LPS[" << i << "] = " << aLps[i] << "\n";
        }
        */
    }

    static int KmpStrstr( const string& haystack, const string& needle )
    {
        if( needle.length() == 0 )
        {
            return 0;
        }

        if( needle.length() > haystack.length() )
        {
            return -1;
        }

        vector<int> lps( needle.length(), 0 );
        buildLps( needle, lps );

        int i = 0; // index for haystack.
        int j = 0; // index for needle.

        while( i < haystack.length() )
        {
            if( haystack[i] == needle[j] )
            {
                i++;
                j++;
            }

            if( j == needle.length() )
            {
                break;
            }
            else if( i < haystack.length() && haystack[i] != needle[j] ) // if not match
            {                
                if( j == 0 )
                {
                    i++;
                }
                else
                {
                    j = lps[j - 1];
                    // No need to increment i.
                }
            }

        }

        return j == needle.length() ? i - j : -1;
    }
};

int main()
{    
    string haystack( "hello" );
    string needle( "ll" );
    std::cout << "strStr (navie ver.):" << Solution::strStr( haystack, needle ) << "\n";

    //haystack = "ABABDABACDABABCABAB";
    //needle = "ABABCABAB";
    haystack = "aaaaa";
    needle = "bba";
    std::cout << "strStr (KMP):" << Solution::KmpStrstr( haystack, needle ) << "\n";

    needle = "pqprpqps";
    vector<int> lps( needle.length(), 0 );
    Solution::buildLps( needle, lps );
    
}
