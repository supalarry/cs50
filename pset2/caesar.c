#include <stdio.h>

int   ft_check(char *str);
void  ft_cipher(char *str, int key);
int   ft_atoi(char *str);

int   main(int argc, char **argv)
{
  char buffer[4096];

  if (argc != 2 || ft_check(argv[1]) == 1)
  {
    printf("Usage: ./caesar key\n");
  }
  else
  {
    printf("plaintext: ");
    if (fgets(buffer, 4096, stdin) != NULL)
    {
      printf("ciphertext: ");
      ft_cipher(buffer, ft_atoi(argv[1]));
      printf("%s", buffer);
    }
  }
}

void  ft_cipher(char *str, int key)
{
  int i;
  int temp;

  i = 0;
  temp = 0;
  while (str[i] != '\0')
  {
    if (str[i] >= 'a' && str[i] <= 'z')
    {
      if (str[i] + key > 'z')
      {
        temp = key - ('z' - str[i]) - 1;
        str[i] = 'a' + temp;
      }
      else
      {
        str[i] = str[i] + key;
      }
    }
    else if (str[i] >= 'A' && str[i] <= 'Z')
    {
      if (str[i] + key > 'Z')
      {
        temp = key - ('Z' - str[i]) - 1;
        str[i] = 'A' + temp;
      }
      else
      {
        str[i] = str[i] + key;
      }
    }
    i++;
  }
}

int   ft_check(char *str)
{
  int i;

  i = 0;
  while (str[i] != '\0')
  {
    if (!(str[i] - 48 >= 0 && str[i] - 48 <= 9))
    {
      return (1);
    }
    i++;
  }
  return (0);
}

int   ft_atoi(char *str)
{
  int i;
  int sum;

  i = 0;
  sum = 0;
  while (str[i] != '\0')
  {
    sum = sum * 10;
    sum = sum + (str[i] - 48);
    i++;
  }
  return (sum);
}
