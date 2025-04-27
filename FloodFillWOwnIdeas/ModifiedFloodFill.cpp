//Adapted from: https://www.techiedelight.com/flood-fill-algorithm/
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <iomanip>
#include "stb_image.h"          //library for manipulating image data
#include "stb_image_write.h"    //library for manipulating image data
using namespace std;
 
// Below arrays detail all eight possible movements
int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
 
// check if it is possible to go to pixel (x, y) from the
// current pixel. The function returns false if the pixel
// has a different color, or it's not a valid pixel
bool isSafe(vector<vector<vector<int>>> const &mat, int x, int y, vector<int> &target)
{
    int tolerance = 10;

    return (x >= 0 && x < static_cast<int>(mat[0].size())) 
            && (y >= 0 && y < static_cast<int>(mat.size()))
            && (abs(mat[y][x][0] - target[0]) <= tolerance
            && abs(mat[y][x][1] - target[1]) <= tolerance
            && abs(mat[y][x][2] - target[2]) <= tolerance);
}
 
// Flood fill using DFS
void floodfill(vector<vector<vector<int>>> &mat, int x, int y, vector<int> &replacement)
{
    // base case
    if (mat.size() == 0) 
    {
        return;
    }
 
    // get the target color
    vector<int> target{mat[y][x][0],mat[y][x][1],mat[y][x][2]};
 
    // target color is same as replacement
    if (target[0] == replacement[0] && target[1] == replacement[1]
        && target[2] == replacement[2]) 
    {
        return;
    }
 
    // replace the current pixel color with that of replacement
    mat[y][x][0] = replacement[0];
    mat[y][x][1] = replacement[1];
    mat[y][x][2] = replacement[2];
 
    // process all eight adjacent pixels of the current pixel and
    // recur for each valid pixel
    for (int k = 0; k < 8; k++)
    {
        // if the adjacent pixel at position (x + row[k], y + col[k]) is
        // a valid pixel and has the same color as that of the current pixel
        if (isSafe(mat, x + row[k], y + col[k], target)) 
        {
            floodfill(mat, x + row[k], y + col[k], replacement);
        }
    }
}

int main()
{
    int width, height, channels;
    unsigned char *image = stbi_load("house.jpg", &width, &height, &channels, 0);

    if(image == nullptr)
    {
        cout << "\n\nERROR LOADING IMAGE!\n\n";
        return 1;
    }
    //matrix showing portion of the screen having different colors
    vector<vector<vector<int>>> mat(height, vector<vector<int>>(width, vector<int>(3)));
    
    //represent the imported image as a 2D vector, where each entry
    //represents the RGB values for a pixel
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int pixel_index = (y * width + x) * channels;
            int R = static_cast<int>(image[pixel_index]);
            int G = static_cast<int>(image[pixel_index + 1]);
            int B = static_cast<int>(image[pixel_index + 2]);
            
            mat[y][x][0] = R;
            mat[y][x][1] = G;
            mat[y][x][2] = B;
        }
    }

    //replace the target color with a replacement color using DFS
    vector<int> replacement{255, 0, 0};
    floodfill(mat, width/3, height/5, replacement);

    //modify the image using the modified matrix
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int index = (y * width + x) * channels;
            image[index] = static_cast<unsigned char>(mat[y][x][0]);
            image[index + 1] = static_cast<unsigned char>(mat[y][x][1]);
            image[index + 2] = static_cast<unsigned char>(mat[y][x][2]);
        }
    }

    //write the modified image to an output file
    stbi_write_jpg("output.jpg", width, height, channels, image, 100);
    //free memory reserved for the image
    stbi_image_free(image);
 
    return 0;
}
//noted limitation: high resolutiom images require high memory usage b/c of
//recursion 
