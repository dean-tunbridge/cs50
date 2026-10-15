#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int average_rgb =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Update pixel values
            image[i][j].rgbtBlue = average_rgb;
            image[i][j].rgbtGreen = average_rgb;
            image[i][j].rgbtRed = average_rgb;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate sepia value for each colour
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // handle number exceeding 255 in calculation
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
             if(sepiaGreen > 255)
             {
                sepiaGreen = 255;
            }
             if(sepiaBlue > 255)
             {
                sepiaBlue = 255;
            }
            // Update pixel values
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2; j++)
        {
            // Reverse each pixel in row
            int opposite_pixel = width - 1 - j;
            RGBTRIPLE stored_pixel = image[i][j];
            image[i][j] = image[i][opposite_pixel];
            image[i][opposite_pixel] = stored_pixel;

        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
     // Loop over all pixels
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2; j++)
        {
            // Get average of 9 pixels surrounding
                              // Get average of pixels either side of current
            int average_rgb = image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                              image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                              image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                              // Get average of pixels above current
                              image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                              image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                              image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                              // TODO Get average of pixels below current //
                              image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                              image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                              image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
        }
    }
}
