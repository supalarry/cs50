#include <stdlib.h>
#include <stdio.h>

int   converter(char *str)
{
  int i;
  int num;
  int sign;

  i = 0;
  num = 0;
  sign = 0;
  while (str[i] != '\n')
  {
    if (str[i] == '-')
    {
      sign = 1;
    }
    else if (str[i] - 48 >= 1 && str[i] - 48 <= 9)
    {
      num = num * 10;
      num = num + (str[i] - 48);
    }
    else if (i != 0 && str[i] - 48 == 0)
    {
      num = num * 10;
      num = num + (str[i] - 48);
    }
    i++;
  }
  if (sign == 1)
  {
    return (-num);
  }
  else
  {
    return (num);
  }
}

int   consists_letter(char *str)
{
  int i;

  i = 0;
  while (str[i] != '\n')
  {
    if (!(str[i] - 48 >= 0 && str[i] - 48 <= 9) && str[i] != '.')
    {
      return (0);
      break;
    }
    i++;
  }
  return (1);
}

int   main(void)
{
  char  *array; // used to store users input of a float
  int   cents; // used to store dollar worth in cents
  int   coins[4]; // used to store possible coins
  int   coins_returned; // count of coins to coins_retur
  int   i;

  array = (char*)malloc(100);
  do
  {
    printf("Change owed: ");
    fgets(array,100, stdin);
    cents = converter(array);
  }while (cents < 0 || (consists_letter(array) == 0));
  coins[0] = 25; // quarter
  coins[1] = 10; // dime
  coins[2] = 5; // nickel
  coins[3] = 1; // penny
  coins_returned = 0;
  i = 0;
  while (cents > 0)
  {
    while (cents % coins[i] != cents)
    {
      coins_returned++;
      cents = cents - coins[i];
    }
    i++;
  }
  printf("Number of coins returned: %d\n", coins_returned);
  free(array);
  return (0);
}
