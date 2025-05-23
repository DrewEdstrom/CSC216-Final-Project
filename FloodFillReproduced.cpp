//Sourced from: https://www.techiedelight.com/flood-fill-algorithm/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
 
// Below arrays detail all eight possible movements
int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
 
// check if it is possible to go to pixel (x, y) from the
// current pixel. The function returns false if the pixel
// has a different color, or it's not a valid pixel
bool isSafe(vector<vector<char>> const &mat, int x, int y, char target)
{
    return (x >= 0 && x < mat.size()) && (y >= 0 && y < mat[0].size())
        && mat[x][y] == target;
}
 
// Flood fill using DFS
void floodfill(vector<vector<char>> &mat, int x, int y, char replacement)
{
    // base case
    if (mat.size() == 0) {
        return;
    }
 
    // get the target color
    char target = mat[x][y];
 
    // target color is same as replacement
    if (target == replacement) {
        return;
    }
 
    // replace the current pixel color with that of replacement
    mat[x][y] = replacement;
 
    // process all eight adjacent pixels of the current pixel and
    // recur for each valid pixel
    for (int k = 0; k < 8; k++)
    {
        // if the adjacent pixel at position (x + row[k], y + col[k]) is
        // a valid pixel and has the same color as that of the current pixel
        if (isSafe(mat, x + row[k], y + col[k], target)) {
            floodfill(mat, x + row[k], y + col[k], replacement);
        }
    }
}
 
// Utility function to print a matrix
void printMatrix(vector<vector<char>> const &mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++) {
            cout << setw(3) << mat[i][j];
        }
        cout << endl;
    }
}
 
int main()
{
    // matrix showing portion of the screen having different colors
    vector<vector<char>> mat =
    {
        { 'Y', 'Y', 'Y', 'G', 'G', 'G', 'G', 'G', 'G', 'G' },
        { 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'G', 'X', 'X', 'X' },
        { 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'X', 'X', 'X' },
        { 'W', 'W', 'W', 'W', 'W', 'G', 'G', 'G', 'G', 'X' },
        { 'W', 'R', 'R', 'R', 'R', 'R', 'G', 'X', 'X', 'X' },
        { 'W', 'W', 'W', 'R', 'R', 'G', 'G', 'X', 'X', 'X' },
        { 'W', 'B', 'W', 'R', 'R', 'R', 'R', 'R', 'R', 'X' },
        { 'W', 'B', 'B', 'B', 'B', 'R', 'R', 'X', 'X', 'X' },
        { 'W', 'B', 'B', 'X', 'B', 'B', 'B', 'B', 'X', 'X' },
        { 'W', 'B', 'B', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
    };
 
    // start node
    int x = 3, y = 9;    // having a target color `X`
 
    // replacement color
    char replacement = 'C';
 
    // replace the target color with a replacement color using DFS
    floodfill(mat, x, y, replacement);
 
    // print the colors after replacement
    printMatrix(mat);
 
    return 0;
}
