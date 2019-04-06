#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

int   main(int argc, char **argv)
{
  if (argc != 4)
  {
    printf("Usage: ./resize n input_file output_file\n");
    return (1);
  }
  char *infile = argv[2];
  char *outfile = argv[3];
  float  multiple = atoll(argv[1]);

  printf("%s\n", multiple);
  FILE *inptr = fopen(infile, "r");
  if (inptr == NULL)
  {
    printf("Could not open source file\n");
    return (2);
  }
  FILE *outptr = fopen(outfile, "w");
  if (outptr == NULL)
  {
    printf("Could not open destination file\n");
    return (3);
  }
  BITMAPFILEHEADER bf;
  BITMAPINFOHEADER bi;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
  BITMAPFILEHEADER bf_new = bf;
  BITMAPINFOHEADER bi_new = bi;
  // adjust file and info headers
  bi_new.biHeight = int(bi_new.biHeight * multiple);
  bi_new.biWidth = int(bi_new.biWidth * multiple);
  int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
  int padding_new = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
  bi_new.biSizeImage = (bi_new.biWidth * sizeof(RGBTRIPLE) + padding_new) * abs(bi_new.biHeight);
  bf_new.bfSize = bf_new.bfSize + 14 + 40;
  fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);
  fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);


  for (int i = 0, biHeight = abs(bi_new.biHeight); i < biHeight; i++)
  {
    int vertical = 0;
    while (vertical < multiple) // resize vertically
    {
      for (int j = 0; j < bi.biWidth; j++)
      {
        RGBTRIPLE triple;
        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        for (int k = 0; k < multiple; k++) // resize horizontally
        {
          fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
      }
      for (int u = 0; u < padding_new; u++)
      {
        fputc(0x00, outptr);
      }
      if (vertical < multiple - 1) // we do not want to reset offset last time
      { // we loop over source line
        fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
      }
      vertical++;
    }
    fseek(inptr, padding, SEEK_CUR); // we instead go forward when done with line
  }
  fclose(inptr);
  fclose(outptr);
  return (0);
}
