#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Converts an image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double avg_intensity = ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0) + 0.5;
            image[i][j].rgbtRed = (int) avg_intensity;
            image[i][j].rgbtGreen = (int) avg_intensity;
            image[i][j].rgbtBlue = (int) avg_intensity;
        }
    }
    return;
}

// Reflects an image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // ONLY iterate for the Left half, otherwise you swap them back
        {
            RGBTRIPLE pixel_swapper = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = pixel_swapper; // minus one as indexed from 0 to width - 1
        }
    }
    return;
}

// Blur image by comparing the pixels around a given pixel and editing its RGB values
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            float red_total;
            float blue_total;
            float green_total;
            int counter;
            red_total = blue_total = green_total = counter = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    if ((i + k < 0) || (i + k >= height))
                    {
                        continue;
                    }

                    if ((j + l < 0) || (j + l >= width))
                    {
                        continue;
                    }

                    red_total += temp[i + k][j + l].rgbtRed;
                    blue_total += temp[i + k][j + l].rgbtBlue;
                    green_total += temp[i + k][j + l].rgbtGreen;
                    counter++;
                }
            }

            image[i][j].rgbtRed = round(red_total / counter);
            image[i][j].rgbtGreen = round(green_total / counter);
            image[i][j].rgbtBlue = round(blue_total / counter);
        }
    }
    return;

}

// Detect edges using the Gx & Gy algorithm
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    \
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};



    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            float Gx_r;
            float Gx_g;
            float Gx_b;
            float Gy_r;
            float Gy_g;
            float Gy_b;
            Gx_r = Gx_g = Gx_b = Gy_r = Gy_g = Gy_b = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }

                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    Gx_r += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_g += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_b += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_r += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_g += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_b += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }
            int red_channel = round(sqrt(Gx_r * Gx_r + Gy_r * Gy_r));
            int green_channel = round(sqrt(Gx_g * Gx_g + Gy_g * Gy_g));
            int blue_channel = round(sqrt(Gx_b * Gx_b + Gy_b * Gy_b));

            if (red_channel > 255)
            {
                red_channel = 255;
            }
            if (green_channel > 255)
            {
                green_channel = 255;
            }
            if (blue_channel > 255)
            {
                blue_channel = 255;
            }

            image[i][j].rgbtRed = red_channel;
            image[i][j].rgbtGreen = green_channel;
            image[i][j].rgbtBlue = blue_channel;
        }
    }
    return;
}
