#include "helpers.h"
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (((image[i][j].rgbtBlue != image[i][j].rgbtRed) && (image[i][j].rgbtBlue != image[i][j].rgbtGreen)) || ((image[i][j].rgbtGreen != image[i][j].rgbtRed) && (image[i][j].rgbtGreen != image[i][j].rgbtBlue)) || ((image[i][j].rgbtRed != image[i][j].rgbtGreen) && (image[i][j].rgbtRed != image[i][j].rgbtBlue)))
            {
                float avg_val = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
                image[i][j].rgbtBlue = avg_val;
                image[i][j].rgbtGreen = avg_val;
                image[i][j].rgbtRed = avg_val;
            }
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtRed = temp[2];
        }
    }
    return;
}

//For average color values
float avg_colors(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float count = 0;
    float sum = 0;

    for (int k = i - 1; k < (i + 2); k++)
    {
        for (int l = j - 1; l < (j + 2); l++)
        {
            if (k < 0 || l < 0 || k >= height || l >= width)
            {
                continue;
            }

            if (color_position == 0)
            {
                sum += image[k][l].rgbtRed;
            }

            else if (color_position == 1)
            {
                sum += image[k][l].rgbtGreen;
            }
            else
            {
                sum += image[k][l].rgbtBlue;
            }
            count++;
        }
    }
    return round(sum / count);
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image1[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = avg_colors(i, j, height, width, image1, 0);
            image[i][j].rgbtGreen = avg_colors(i, j, height, width, image1, 1);
            image[i][j].rgbtBlue = avg_colors(i, j, height, width, image1, 2);
        }
    }
    return;
}


//Sobel algorithm for detecting edges
int sobel(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float sumX = 0;
    float sumY = 0;

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int k = i - 1, x = 0; k < (i + 2); k++, x++)
    {
        for (int l = j - 1, y = 0; l < (j + 2); l++, y++)
        {
            if (k < 0 || l < 0 || k >= height || l >= width)
            {
                continue;
            }

            if (color_position == 0)
            {
                sumX += image[k][l].rgbtRed * Gx[x][y];
                sumY += image[k][l].rgbtRed * Gy[x][y];
            }

            else if (color_position == 1)
            {
                sumX += image[k][l].rgbtGreen * Gx[x][y];
                sumY += image[k][l].rgbtGreen * Gy[x][y];
            }

            else
            {
                sumX += image[k][l].rgbtBlue * Gx[x][y];
                sumY += image[k][l].rgbtBlue * Gy[x][y];
            }
        }
    }
    int result = round(sqrt((sumX * sumX) + (sumY * sumY)));
    return result < 255 ? result : 255;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image1[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = sobel(i, j, height, width, image1, 0);
            image[i][j].rgbtGreen = sobel(i, j, height, width, image1, 1);
            image[i][j].rgbtBlue = sobel(i, j, height, width, image1, 2);
        }
    }
    return;
}
