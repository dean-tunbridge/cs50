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
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  return;
}
