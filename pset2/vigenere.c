#include <stdio.h>

int   ft_check(char *str);
void  ft_cipher(char *str, char *key);

int   main(int argc, char **argv)
{
  char buffer[4096];

  if (argc != 2 || ft_check(argv[1]) == 1)
  {
    printf("Usage: ./caesar keyword\n");
  }
  else
  {
    printf("plaintext: ");
    if (fgets(buffer, 4096, stdin) != NULL)
    {
      printf("ciphertext: ");
      ft_cipher(buffer, argv[1]);
      printf("%s", buffer);
    }
  }
}

void  ft_cipher(char *str, char *key)
{
  int i; //bacon dog -> bacon 3 14 6
  int temp;
  int x;
  int alpha;

  i = 0; //track string
  temp = 0;
  x = 0; //track key
  while (str[i] != '\0')
  {
    if (key[x] >= 'a' && key[x] <= 'z')
    {
      temp = key[x] - 'a';
    }
    else if (key[x] >= 'A' && key[x] <= 'Z')
    {
      temp = key[x] - 'A';
    }
    if (str[i] >= 'a' && str[i] <= 'z')
    {
      if (str[i] + temp > 'z')
      {
        temp = temp - ('z' - str[i]) - 1;
        str[i] = 'a' + temp;
      }
      else
      {
        str[i] = str[i] + temp;
      }
      alpha = 1;
    }
    else if (str[i] >= 'A' && str[i] <= 'Z')
    {
      if (str[i] + temp > 'Z')
      {
        temp = temp - ('Z' - str[i]) - 1;
        str[i] = 'A' + temp;
      }
      else
      {
        str[i] = str[i] + temp;
      }
      alpha = 1;
    }
    i++;
    if (key[x + 1] != '\0' && alpha == 1)
    {
      x++;
    }
    else if (key[x + 1] == '\0' && alpha == 1)
    {
      x = 0;
    }
    alpha = 0;
  }
}

int   ft_check(char *str)
{
  int i;

  i = 0;
  while (str[i] != '\0')
  {
    if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z'))
    {
      return (1);
    }
    i++;
  }
  return (0);
}
