#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int red;
    int green;
    int blue;
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;
            average = round((red + green + blue) / 3.0f);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed;
    int originalGreen;
    int originalBlue;

    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // First we multiply the colors by the algorithm, and we round the sum
            // fmin will return the smaller between the sum and 255, ensuring the max is 255
            // (int) to remove decimals
            sepiaRed = (int) fmin(
                round((.393 * originalRed + .769 * originalGreen + .189 * originalBlue)), 255);
            sepiaGreen = (int) fmin(
                round((.349 * originalRed + .686 * originalGreen + .168 * originalBlue)), 255);
            sepiaBlue = (int) fmin(
                round((.272 * originalRed + .534 * originalGreen + .131 * originalBlue)), 255);

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurImage[height][width];

    int red;
    int green;
    int blue;

    int averageCounter;
    int averageRed = 0;
    int averageGreen = 0;
    int averageBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = 0;
            green = 0;
            blue = 0;
            averageCounter = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                if (k < 0 || k >= height)
                {
                    continue;
                }
                for (int p = j - 1; p <= j + 1; p++)
                {
                    if (p < 0 || p >= width)
                    {
                        continue;
                    }
                    red += image[k][p].rgbtRed;
                    green += image[k][p].rgbtGreen;
                    blue += image[k][p].rgbtBlue;
                    averageCounter++;
                }
            }

            averageRed = round(red / (float) averageCounter);
            averageGreen = round(green / (float) averageCounter);
            averageBlue = round(blue / (float) averageCounter);

            blurImage[i][j].rgbtRed = averageRed;
            blurImage[i][j].rgbtGreen = averageGreen;
            blurImage[i][j].rgbtBlue = averageBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurImage[i][j];
        }
    }

    return;
}
