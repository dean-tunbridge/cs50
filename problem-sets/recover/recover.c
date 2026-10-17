#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  // Accept a single command-line argument
  if (argc != 2)
  {
    printf("Usage: ./recover FILE\n");
    return 1;
  }

  // Open the memory card
  FILE *card = fopen(argv[1], "r");
  if (!card)
  {
    printf("Error, unable to open memory card");
    return 1;
  }

  // Create a buffer for a block of data
  int block_size = 512;
  uint8_t buffer[block_size];

  // Declare filename before usse to fix compiling issue
  char filename[9];
  // initialise count
  int count = 0;
  // initialise image pointer
  FILE *img = NULL;

  // While there's still data left to read from the memory card
  while (fread(buffer, 1, block_size, card) == block_size)
  {
    // Create JPEGs from the data

    // Check byte values against expected JPEG values
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
    {
      // if There is an open image, close it
      if (img != NULL)
      {
        fclose(img);
      }
      // create filename for jpgs
      sprintf(filename, "%03i.jpg", count);
      img = fopen(filename, "w");
      // Increment count for filename
      count++;
    }
    if (img)
    {
      // If there is an image, write
      fwrite(buffer, 1, block_size, img);
    }
  }
  if (img != NULL)
  {
    fclose(img);
  }
  fclose(card);
}
