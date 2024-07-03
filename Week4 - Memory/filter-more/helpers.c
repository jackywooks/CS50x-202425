#include "helpers.h"
#include <math.h>

// Prototype
int clamp(int value, int min, int max);

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
    // // checker
    // height = 3;
    // width = 3;

    // image[0][0].rgbtRed = 0;
    // image[0][0].rgbtGreen = 10;
    // image[0][0].rgbtBlue = 25;

    // image[0][1].rgbtRed = 0;
    // image[0][1].rgbtGreen = 10;
    // image[0][1].rgbtBlue = 30;

    // image[0][2].rgbtRed = 40;
    // image[0][2].rgbtGreen = 60;
    // image[0][2].rgbtBlue = 80;

    // image[1][0].rgbtRed = 20;
    // image[1][0].rgbtGreen = 30;
    // image[1][0].rgbtBlue = 90;

    // image[2][0].rgbtRed = 20;
    // image[2][0].rgbtGreen = 20;
    // image[2][0].rgbtBlue = 40;

    int padded_height = height + 2;
    int padded_width = width + 2;
    RGBTRIPLE padded_image[padded_height][padded_width];

    for (int i = 0; i < padded_height; i++)
    {
        for (int j = 0; j < padded_width; j++)
        {
            if (i == 0 || j == 0 || i == padded_height - 1 || j == padded_width - 1)
            {
                padded_image[i][j].rgbtRed = 0;
                padded_image[i][j].rgbtGreen = 0;
                padded_image[i][j].rgbtBlue = 0;
            }
            else
            {
                padded_image[i][j] = image[i - 1][j - 1];
            }
        }
    }

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            // Initiate the Gx and Gy
            int GxRed = 0;
            int GyRed = 0;
            int GxGreen = 0;
            int GyGreen = 0;
            int GxBlue = 0;
            int GyBlue = 0;

            // initiate the Gx, Gy value in kernel
            int GxTopLeft = -1;
            int GxLeft = -2;
            int GxBottomLeft = -1;
            int GxTopMiddle = 0;
            int GxMiddle = 0;
            int GxBottomMiddle = 0;
            int GxTopRight = 1;
            int GxRight = 2;
            int GxBottomRight = 1;

            int GyTopLeft = -1;
            int GyLeft = 0;
            int GyBottomLeft = 1;
            int GyTopMiddle = -2;
            int GyMiddle = 0;
            int GyBottomMiddle = 2;
            int GyTopRight = -1;
            int GyRight = 0;
            int GyBottomRight = 1;

            // Handling pixel above
            if (i > 0)
            {
                // i, j + 1 box
                GxRed += padded_image[i][j + 1].rgbtRed * GxTopMiddle;
                GxGreen += padded_image[i][j + 1].rgbtGreen * GxTopMiddle;
                GxBlue += padded_image[i][j + 1].rgbtBlue * GxTopMiddle;

                GyRed += padded_image[i][j + 1].rgbtRed * GyTopMiddle;
                GyGreen += padded_image[i][j + 1].rgbtGreen * GyTopMiddle;
                GyBlue += padded_image[i][j + 1].rgbtBlue * GyTopMiddle;
            }

            // Handling the top-left pixel
            if (i > 0 && j > 0)
            {
                // i, j box
                GxRed += padded_image[i][j].rgbtRed * GxTopLeft;
                GxGreen += padded_image[i][j].rgbtGreen * GxTopLeft;
                GxBlue += padded_image[i][j].rgbtBlue * GxTopLeft;

                GyRed += padded_image[i][j].rgbtRed * GyTopLeft;
                GyGreen += padded_image[i][j].rgbtGreen * GyTopLeft;
                GyBlue += padded_image[i][j].rgbtBlue * GyTopLeft;
            }

            // Handling Pixel on the left
            if (j > 0)
            {
                // i + 1, j box
                GxRed += padded_image[i + 1][j].rgbtRed * GxLeft;
                GxGreen += padded_image[i + 1][j].rgbtGreen * GxLeft;
                GxBlue += padded_image[i + 1][j].rgbtBlue * GxLeft;

                GyRed += padded_image[i + 1][j].rgbtRed * GyLeft;
                GyGreen += padded_image[i + 1][j].rgbtGreen * GyLeft;
                GyBlue += padded_image[i + 1][j].rgbtBlue * GyLeft;
            }

            // Handling the bottom-left pixel
            if (j > 0 && i < height - 1)
            {
                // i + 2, j  box
                GxRed += padded_image[i + 2][j].rgbtRed * GxBottomLeft;
                GxGreen += padded_image[i + 2][j].rgbtGreen * GxBottomLeft;
                GxBlue += padded_image[i + 2][j].rgbtBlue * GxBottomLeft;

                GyRed += padded_image[i + 2][j].rgbtRed * GyBottomLeft;
                GyGreen += padded_image[i + 2][j].rgbtGreen * GyBottomLeft;
                GyBlue += padded_image[i + 2][j].rgbtBlue * GyBottomLeft;
            }

            // Handling bottom pixel
            if (i < height - 1)
            {
                // i + 2 , j + 1box
                GxRed += padded_image[i + 2][j + 1].rgbtRed * GxBottomMiddle;
                GxGreen += padded_image[i + 2][j + 1].rgbtGreen * GxBottomMiddle;
                GxBlue += padded_image[i + 2][j + 1].rgbtBlue * GxBottomMiddle;

                GyRed += padded_image[i + 2][j + 1].rgbtRed * GyBottomMiddle;
                GyGreen += padded_image[i + 2][j + 1].rgbtGreen * GyBottomMiddle;
                GyBlue += padded_image[i + 2][j + 1].rgbtBlue * GyBottomMiddle;
            }

            // Handling the bottom-right pixel
            if (i < height - 1 && j < width - 1)
            {
                // i + 2, j + 2 box
                GxRed += padded_image[i + 2][j + 2].rgbtRed * GxBottomRight;
                GxGreen += padded_image[i + 2][j + 2].rgbtGreen * GxBottomRight;
                GxBlue += padded_image[i + 2][j + 2].rgbtBlue * GxBottomRight;

                GyRed += padded_image[i + 2][j + 2].rgbtRed * GyBottomRight;
                GyGreen += padded_image[i + 2][j + 2].rgbtGreen * GyBottomRight;
                GyBlue += padded_image[i + 2][j + 2].rgbtBlue * GyBottomRight;
            }

            // Handling Pixel on the right
            if (j < width - 1)
            {
                // i + 1, j + 2 box
                GxRed += padded_image[i + 1][j + 2].rgbtRed * GxRight;
                GxGreen += padded_image[i + 1][j + 2].rgbtGreen * GxRight;
                GxBlue += padded_image[i + 1][j + 2].rgbtBlue * GxRight;

                GyRed += padded_image[i + 1][j + 2].rgbtRed * GyRight;
                GyGreen += padded_image[i + 1][j + 2].rgbtGreen * GyRight;
                GyBlue += padded_image[i + 1][j + 2].rgbtBlue * GyRight;
            }

            // Handling the top right pixel
            if (i > 0 && j < width - 1)
            {
                // i, j + 2 box
                GxRed += padded_image[i][j + 2].rgbtRed * GxTopRight;
                GxGreen += padded_image[i][j + 2].rgbtGreen * GxTopRight;
                GxBlue += padded_image[i][j + 2].rgbtBlue * GxTopRight;

                GyRed += padded_image[i][j + 2].rgbtRed * GyTopRight;
                GyGreen += padded_image[i][j + 2].rgbtGreen * GyTopRight;
                GyBlue += padded_image[i][j + 2].rgbtBlue * GyTopRight;
            }

            // Average the pixels
            int combineRed = clamp(round(sqrt(GxRed * GxRed + GyRed * GyRed)), 0, 255);
            int combineGreen = clamp(round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen)), 0, 255);
            int combineBlue = clamp(round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue)), 0, 255);

            // Put the averaged pixels color in the temp array
            image[i][j].rgbtRed = combineRed;
            image[i][j].rgbtGreen = combineGreen;
            image[i][j].rgbtBlue = combineBlue;
        }
    }

    return;
}

int clamp(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    return value;
}
