#include <stdlib.h>
#include <stdio.h>

int   strlength(char *str) //returns length. if string contains any other
{ // character than a number, then it returns 0.
  int i;
  int restricted;

  i = 0;
  restricted = 0;
  while (str[i] != '\n')
  {
    if (!(str[i] - 48 >= 0 && str[i] - 48 <= 9))
    {
      restricted++;
    }
    i++;
  }
  if (restricted == 0)
  {
    return (i);
  }
  else
  {
    return (0);
  }
}

void  card_name(char *str)
{
  if (str[0] == '4') // visa cards start with 4
  {
    printf("VISA\n");
  }
  else if (str[0] == '3' && (str[1] == '4' || str[1] == '7'))
  { // american express cards start with 34 or 37
    printf("AMEX\n");
  }
  else if (str[0] == '5' && (str[1] == '1' || str[1] == '2' || str[1] == '3'
  || str[1] == '4' || str[1] == '5'))
  { // master card cards start with 51,52,53,54,55
    printf("MASTERCARD\n");
  }
}

int   checksum(char *str) // every second digit from end of the number is
{ // doubled. Other numbers are simply added to sum. The sum of doubled numbers products is added to total sum.
  int counter;
  int len;
  int sum;
  int temp;

  counter = 1;
  len = strlength(str) - 1;
  sum = 0;
  while (len >= 0)
  {
    if (counter % 2 == 0)
    {
      temp = (str[len] - 48) * 2;
      if (temp >= 0 && temp <= 9)
      {
        sum = sum + temp;
      }
      else
      {
        while (temp != 0)
        {
          sum = sum + (temp % 10);
          temp = temp / 10;
        }
      }
    }
    else
    {
      sum = sum + (str[len] - 48);
    }
    len--;
    counter++;
  }
  if (sum % 10 == 0)
  {
    return (1);
  }
  else
  {
    return (0);
  }
}

int   main(void)
{
  char *array; // store user's card number

  array = (char*)malloc(20); // allocate enough memory
  do
  {
    printf("Number: ");
    fgets(array, 20, stdin); // read user's input
  }while(strlength(array) != 13 && strlength(array) != 15 && strlength(array) != 16);
  // while length of number is not equal to length of American Express, VISA
  // or Master Card, keep asking user for number that is of correct length.
  if (checksum(array) == 1) // check card number using Luhn's Alghoritm
  { // return 1 if card's checksum is valid
    card_name(array); // pass the number further to print credit card company
  }
  else
  {
    printf("INVALID\n");
  }
  free(array);
  return (0);
}
