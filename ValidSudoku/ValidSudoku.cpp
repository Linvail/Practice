#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution
{
public:
    static bool isValidSudoku( vector<vector<char>>& board )
    {
        const size_t boardSize = board.size();

        // We need to define the Id to identify each box.
        /*
        * 0 1 2
        * 3 4 5
        * 6 7 8
        */
        vector<vector<char>> nineBoxes( 9 );

        for( size_t i = 0; i < boardSize; ++i )
        {
            if( !isValidVector( board[i] ) )
            {
                return false;
            }

            vector<char> column;
            for( size_t j = 0; j < boardSize; ++j )
            {
                column.push_back( board[j][i] );

                size_t boxId = ( j / 3 ) + ( ( i / 3 ) * 3 );
                nineBoxes[boxId].push_back( board[i][j] );
            }
            if( !isValidVector( column ) )
            {
                return false;
            }
        }

        for( size_t k = 0; k < boardSize; ++k )
        {
            if( !isValidVector( nineBoxes[k] ) )
            {
                return false;
            }
        }

        return true;
    }

    static bool isValidVector( const vector<char>& aData )
    {
        set<char> uniqueSet;
        for( size_t i = 0; i < aData.size(); ++i )
        {
            if( aData[i] == '.' )
            {
                continue;
            }
            else
            {
                if( uniqueSet.find( aData[i] ) != uniqueSet.end() )
                {
                    return false;
                }
                uniqueSet.insert( aData[i] );
            }
        }
        return true;
    }
};

int main()
{
    vector<vector<char>> testData {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    cout << "isValidSudoku: " << Solution::isValidSudoku( testData ) << endl;
}