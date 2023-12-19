#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int averaged = round(((float) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = averaged;
            image[i][j].rgbtGreen = averaged;
            image[i][j].rgbtRed = averaged;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp_pixel = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            copy[m][n] = image[m][n];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // ARRAY of relevant pixels
            RGBTRIPLE box_array[9];
            // NEXT ROW
                // RGBTRIPLE top_left = image[i - 1][j - 1];
                // RGBTRIPLE top_middle = image[i - 1][j];
                // RGBTRIPLE top_right = image[i - 1][j + 1];
            if (i != 0) {
                if (j != 0) {
                    box_array[0] = copy[i - 1][j - 1];
                }
                box_array[1] = copy[i - 1][j];
                if (j != width - 1) {
                    box_array[2] = copy[i - 1][j + 1];
                }
            }

            // CURRENT ROW get pixel structs from before and after current j index
                // RGBTRIPLE curr_left = image[i][j - 1];
                // RGBTRIPLE curr_middle = image[i][j];
                // RGBTRIPLE curr_right = image[i][j + 1];
            if (j != 0) {
                box_array[3] = copy[i][j - 1];
            }
            box_array[4] = copy[i][j];
            if (j != width - 1) {
                box_array[5] = copy[i][j + 1];
            }

            // NEXT ROW
                // RGBTRIPLE bottom_left = image[i + 1][j - 1];
                // RGBTRIPLE bottom_middle = image[i + 1][j];
                // RGBTRIPLE bottom_rightt = image[i + 1][j + 1];
            if (i != height - 1) // Is the height zero indexed?
            {
                if (j != 0) {
                    box_array[6] = copy[i + 1][j - 1];
                }
                box_array[7] = copy[i + 1][j];
                if (j != width - 1) {
                    box_array[8] = copy[i + 1][j + 1];
                }

            }

            int sum_of_reds = 0;
            int sum_of_greens = 0;
            int sum_of_blues = 0;

            int count = 0;
            for (int k = 0; k < 9; k++) {
                if (box_array[k].rgbtRed) {
                    sum_of_reds += box_array[k].rgbtRed;
                    sum_of_greens += box_array[k].rgbtGreen;
                    sum_of_blues += box_array[k].rgbtBlue;
                    count++;
                }
            }
            int average_of_reds = round((float) sum_of_reds / (float) count);
            int average_of_greens = round((float) sum_of_greens / (float) count);
            int average_of_blues = round((float) sum_of_blues / (float) count);

            image[i][j].rgbtRed = average_of_reds;
            image[i][j].rgbtGreen = average_of_greens;
            image[i][j].rgbtBlue = average_of_blues;
            // printf("The count is... %i\n", count);
        }
    }
    return;
}

                                            // typedef struct
                                            // {
                                            //     BYTE  rgbtBlue;
                                            //     BYTE  rgbtGreen;
                                            //     BYTE  rgbtRed;
                                            // } __attribute__((__packed__))
                                            // RGBTRIPLE;
