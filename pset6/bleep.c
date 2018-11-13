#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*Usage ./bleep banned.txt, where banned.txt contains words to be
censored. Each word to be censored has to be in new line.
if banned.txt contains "gtfo" and you input into command line
when prompted 'coding or gtfo', the program prints coding or **** */

typedef struct node
{
  char word[46];
  struct node *next;
}node;

node *head = NULL;

int ft_strlen(char *str)
{
  int i = 0;
  while (str[i] != '\0')
  {
    i++;
  }
  return (i);
}

void ft_strcpy(char *one, char *two)
{
  int i = 0;
  while (two[i] != '\0')
  {
    one[i] = two[i];
    i++;
  }
  one[i] = '\0';
}

int ft_strcmp(char *one, char *two)
{
  int i = 0;
  while (one[i] != '\0' && two[i] != '\0' && (one[i] == two[i] || one[i] == two[i] + 32))
  {
    i++;
  }
  if (one[i] - two[i] == 0)
  {
    return (1);
  }
  else
  {
    return (0);
  }
}

node *ft_create(char *str)
{
  node *n;
  n = malloc(sizeof(node));
  ft_strcpy(n->word, str);
  n->next = NULL;
  return (n);
}

void ft_insert(node *head, char *str)
{
  node *head_copy = head;
  while (head_copy->next != NULL)
  {
    head_copy = head_copy->next;
  }
  node *n;
  n = malloc(sizeof(node));
  ft_strcpy(n->word, str);
  head_copy->next = ft_create(str);
}

int ft_check(node *head, char *str)
{
  node *head_copy = head;
  while (head_copy != NULL)
  {
    if (ft_strcmp(head_copy->word, str))
    {
      return (1);
    }
    head_copy = head_copy->next;
  }
  return (0);
}

void ft_free(node *head)
{
  if (head->next == NULL)
  {
    return;
  }
  return (ft_free(head->next));
  free(head);
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Usage: ./bleep banned.txt\n");
    return (1);
  }
  printf("What message would you like to censor?\n");
  char buffer[4096]; // store the input line
  fgets(buffer, 4095, stdin);

  FILE *file = fopen(argv[1], "r"); // create banned word link list
  char word[46];
  while (fscanf(file, "%s", word) != EOF)
  {
    if (head == NULL)
    {
      head = ft_create(word);
    }
    else
    {
      ft_insert(head, word);
    }
  }
  char item[46];
  int i = 0;
  int len = ft_strlen(buffer);
  for (int h = 0; h < len; h++)
  {
    if ((buffer[h] >= 'a' && buffer[h] <= 'z') || (buffer[h] >= 'A' && buffer[h] <= 'Z'))
    {
      item[i] = buffer[h];
      i++;
    }
    else if (i > 0)
    {
      item[i] = '\0';
      if (ft_check(head, item) == 1)
      {
        int word_len = ft_strlen(item);
        for (int g = 0; g < word_len; g++)
        {
          write(1, "*", 1);
        }
      }
      else
      {
        printf("%s", item);
        fflush(stdout);
      }
      i = 0;
      if (buffer[h+1] != '\0')
      {
        write(1, " ", 1);
      }
    }
  }
  write(1, "\n", 1);
  ft_free(head);
}
