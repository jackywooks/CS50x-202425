#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // For GrayScale, averaged the rgb to get the brightness
            // and zerolize the color
            int average = round((red + green + blue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // swap the j pixel to width - j pixel
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = red;
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtBlue = blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 1;
            int redSum = image[i][j].rgbtRed;
            int greenSum = image[i][j].rgbtGreen;
            int blueSum = image[i][j].rgbtBlue;

            // Handling pixel above
            if (i > 0)
            {
                // i - 1 , j box
                redSum += image[i - 1][j].rgbtRed;
                greenSum += image[i - 1][j].rgbtGreen;
                blueSum += image[i - 1][j].rgbtBlue;
                counter++;
            }

            // Handling the top-left pixel
            if (i > 0 && j > 0)
            {
                // i - 1, j - 1 box
                redSum += image[i - 1][j - 1].rgbtRed;
                greenSum += image[i - 1][j - 1].rgbtGreen;
                blueSum += image[i - 1][j - 1].rgbtBlue;
                counter++;
            }

            // Handling Pixel on the left
            if (j > 0)
            {
                // i, j - 1 box
                redSum += image[i][j - 1].rgbtRed;
                greenSum += image[i][j - 1].rgbtGreen;
                blueSum += image[i][j - 1].rgbtBlue;
                counter++;
            }

            // Handling the bottom-left pixel
            if (j > 0 && i < height - 1)
            {
                // i + 1, j - 1 box
                redSum += image[i + 1][j - 1].rgbtRed;
                greenSum += image[i + 1][j - 1].rgbtGreen;
                blueSum += image[i + 1][j - 1].rgbtBlue;
                counter++;
            }

            // Handling bottom pixel
            if (i < height - 1)
            {
                // i + 1 , j box
                redSum += image[i + 1][j].rgbtRed;
                greenSum += image[i + 1][j].rgbtGreen;
                blueSum += image[i + 1][j].rgbtBlue;
                counter++;
            }

            // Handling the bottom-right pixel
            if (i < height - 1 && j < width - 1)
            {
                // i + 1, j + 1 box
                redSum += image[i + 1][j + 1].rgbtRed;
                greenSum += image[i + 1][j + 1].rgbtGreen;
                blueSum += image[i + 1][j + 1].rgbtBlue;
                counter++;
            }

            // Handling Pixel on the right
            if (j < width - 1)
            {
                // i , j + 1 box
                redSum += image[i][j + 1].rgbtRed;
                greenSum += image[i][j + 1].rgbtGreen;
                blueSum += image[i][j + 1].rgbtBlue;
                counter++;
            }

            // Handling the top right pixel
            if (i > 0 && j < width - 1)
            {
                // i - 1, j + 1 box
                redSum += image[i - 1][j + 1].rgbtRed;
                greenSum += image[i - 1][j + 1].rgbtGreen;
                blueSum += image[i - 1][j + 1].rgbtBlue;
                counter++;
            }

            // Average the pixels
            int redAvg = round((float) redSum / counter);
            int greenAvg = round((float) greenSum / counter);
            int blueAvg = round((float) blueSum / counter);

            // Put the averaged pixels color in the temp array
            temp[i][j].rgbtRed = redAvg;
            temp[i][j].rgbtGreen = greenAvg;
            temp[i][j].rgbtBlue = blueAvg;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
        }
    }
    return;
}
