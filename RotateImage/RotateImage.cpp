// RotateImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // Transpose and reserve each row.
    static void rotate( vector<vector<int>>& matrix )
    {
        // Transpose
        const size_t MatrixSize = matrix.size();
        for( size_t i = 0; i < MatrixSize; i++ )
        {
            for( size_t j = i; j < MatrixSize; j++ )
            {
                std::swap( matrix[i][j], matrix[j][i] );
            }
        }

        // reverse each row.
        for( size_t i = 0; i < MatrixSize; i++ )
        {
            std::reverse( matrix[i].begin(), matrix[i].end() );
        }
    }

    // Transpose and reserve each column.
    static void rotateAnticlockwise( vector<vector<int>>& matrix )
    {
        // Transpose
        const size_t MatrixSize = matrix.size();
        for( size_t i = 0; i < MatrixSize; i++ )
        {
            for( size_t j = i; j < MatrixSize; j++ )
            {
                std::swap( matrix[i][j], matrix[j][i] );
            }
        }

        // Reverse each column.
        for( size_t i = 0; i < MatrixSize; i++ )
        {
            size_t k = MatrixSize - 1;
            for( size_t j = 0; j < k; ++j, --k )
            {
                std::swap( matrix[j][i], matrix[k][i] );
            }
        }

    }
};

int main()
{
    std::cout << "Rotate Image!\n";

    const size_t MatrixSize = 3;
    vector<vector<int>> testData {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Rotate 90 degrees clockwise.
    Solution::rotate( testData );

    // Printing matrix elements after rotation
    cout << "\nMatrix after rotating 90 degree clockwise:\n";
    for( int i = 0; i < MatrixSize; i++ )
    {
        for( int j = 0; j < MatrixSize; j++ )
        {
            cout << testData[i][j] << " ";
        }
        cout << "\n";
    }

    // Rotate 90 degrees anti-clockwise.
    Solution::rotateAnticlockwise( testData );

    // Printing matrix elements after rotation
    cout << "\nMatrix after rotating 90 degree clockwise:\n";
    for( int i = 0; i < MatrixSize; i++ )
    {
        for( int j = 0; j < MatrixSize; j++ )
        {
            cout << testData[i][j] << " ";
        }
        cout << "\n";
    }
}
