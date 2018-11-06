#include <stdlib.h>
#include <stdio.h>

int   main(int argc, char **argv)
{
  FILE *input = fopen(argv[1], "r");
  FILE *picture = NULL;
  unsigned char buffer[512];
  int img_count = 0;
  int jpeg_found = 0;

  while (fread(buffer, 512, 1, input) == 1)
  {
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
    {
      if (jpeg_found)
      {
        fclose(picture);
      }
      else
      {
        jpeg_found = 1;
      }
      char filename[8];
      sprintf(filename, "%pset3.jpg", img_count);
      picture = fopen(filename, "w");
      img_count++;
    }
    if (jpeg_found)
    {
      fwrite(buffer, 512, 1, picture);
    }
  }
  fclose(input);
  fclose(picture);
  return (0);
}
