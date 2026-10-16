#include "helpers.h"
#include <math.h>

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

// Helper function for boundary checking
int boundary_check(int colour)
{
  if (colour > 255)
  {
    colour = 255;
  }
  return colour;
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
      int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                           .189 * image[i][j].rgbtBlue);
      int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                             .168 * image[i][j].rgbtBlue);
      int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                            .131 * image[i][j].rgbtBlue);

      // handle number exceeding 255 in calculation
      sepiaRed = boundary_check(sepiaRed);
      sepiaGreen = boundary_check(sepiaGreen);
      sepiaBlue = boundary_check(sepiaBlue);

      // Update pixel values
      image[i][j].rgbtRed = sepiaRed;
      image[i][j].rgbtGreen = sepiaGreen;
      image[i][j].rgbtBlue = sepiaBlue;
    }
  }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  // Loop over all pixels
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width / 2; j++)
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
  // Create new array to push blurred pixels to
  RGBTRIPLE new_image[height][width];

  // Loop over all pixels
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // Initiate count for each colour
      int blue_count = 0;
      int green_count = 0;
      int red_count = 0;
      // initiate variable to check how many valid pixels surround the current pixel
      int surrounding_count = 0;

      // Loop through the surrounding grid and check for valid pixels
      for (int row = -1; row < 2; row++)
      {
        for (int column = -1; column < 2; column++)
        {
          // Check for boundary
          if (i + row >= 0 && i + row < height && j + column >= 0 && j + column < width)
          {
            // Add values for each
            blue_count += image[i + row][j + column].rgbtBlue;
            green_count += image[i + row][j + column].rgbtGreen;
            red_count += image[i + row][j + column].rgbtRed;
            // Add to surrounding count for division
            surrounding_count++;
          }
        }
      }
      // Calculate averages for each colour
      int blue_average = round((float)blue_count / surrounding_count);
      int green_average = round((float)green_count / surrounding_count);
      int red_average = round((float)red_count / surrounding_count);

      // Add new RGB values to corresponding value in new_image array
      new_image[i][j].rgbtBlue = blue_average;
      new_image[i][j].rgbtGreen = green_average;
      new_image[i][j].rgbtRed = red_average;
    }
  }
  // Replace original values with the blurred values
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      // Replace original value with blurred value
      image[i][j] = new_image[i][j];
    }
  }
}
