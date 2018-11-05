#include <stdio.h>
#include <stdlib.h>

int   atoii(char *str)
{
  int num;
  int i;

  num = 0;
  i = 0;
  while (str[i] != '\0')
  {
    num = num * 10;
    num = num + (str[i] - 48);
    i++;
  }
  return (num);
}

int   main(int argc, char **argv)
{
  int current_level;
  char *input;
  int height;

  //height = atoi(argv[1]);
  input = (char*)malloc(100);
  fgets(input, 100, stdin);
  height = atoi(input);
  free(input);
  current_level = 1;
  printf("Height: %d\n", height);
  if (height >= 1 && height <= 8)
  {
    while (current_level <= height)
    {
      for (int i = 0; i < (height - current_level); i++)
      {
        printf("%c",' ');
      }
      for (int i = 0; i < current_level; i++)
      {
        printf("%c",'#');
      }
      printf("%c",'\n');
      current_level++;
    }
  }
  return (0);
}
