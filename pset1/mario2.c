#include <stdlib.h>
#include <stdio.h>

int   converter(char *str)
{
  int i;
  int num; // stores converted string as a number
  int sign; // used to return negative number if minus is encountered

  i = 0;
  num = 0;
  sign = 0;
  while (str[i] != '\n')
  {
    if (str[i] == '-')
    {
      sign = 1;
    }
    else if (str[i] - 48 >= 1 && str[i] - 48 <= 8)
    {
      num = num * 10;
      num = num + (str[i] - 48);
    }
    i++;
  }
  if (sign == 1)
  {
    return(-num);
  }
  else
  {
    return (num);
  }
}

int   main(void)
{
  char  *array; // used to store user input
  int   height; // stores user input converted to an integer
  int   level; // stores current level vertically, and is number of hashes to be printed
  // number of spaces is calculated as height (its same as width) minus level

  array = (char*)malloc(sizeof(int) * 4); // allocate memory to user input
  height = converter(fgets(array, 16, stdin)); // read input and convert to number
  level = 1;
  printf("Height: %d\n", height);
  if (height >= 1 && height <= 8) // allowed height values are between 1 and 8
  {
    while (level <= height)
    {
      for (int i = 0; i < (height - level); i++)
      {
        printf("%c", ' ');
      }
      for (int i = 0; i < level; i++)
      {
        printf("%c", '#');
      }
      printf("%c", ' ');
      printf("%c", ' ');
      for (int i = 0; i < level; i++)
      {
        printf("%c", '#');
      }
      for (int i = 0; i < (height - level); i++)
      {
        printf("%c", ' ');
      }
      printf("\n");
      level++;
    }
  }
  else
  {
    printf("\nHeight must be between 1 and 8 inclusive\n");
  }

}
