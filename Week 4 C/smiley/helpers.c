#include "helpers.h"
#include "stdio.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%i %i %i\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            if (image[i][j].rgbtRed == 0)
            {
                image[i][j].rgbtRed = 255;
            }
            if (image[i][j].rgbtGreen == 0)
            {
                image[i][j].rgbtGreen = 255;
            }
            if (image[i][j].rgbtBlue == 0)
            {
                image[i][j].rgbtBlue = 0;
            }
        }
    }
}

// 85/30/138 --> a kind of purple
// 255/255/0 --> a yellow
