#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void  ft_decrypt(char *str)
{
  char buffer[6] = "\0";
  char alpha[53] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  int  found = 0, a = -1, b = -1, c = -1, d = -1, e = 0;

  while (a < 52 && found == 0)
  {
    while (b < 52 && found == 0)
    {
      while (c < 52 && found == 0)
      {
        while (d < 52 && found == 0)
        {
          while (e < 52 && found == 0)
          {
            buffer[0] = alpha[e];
            if (d >= 0)
              buffer[1] = alpha[d];
            if (c >= 0)
              buffer[2] = alpha[c];
            if (b >= 0)
              buffer[3] = alpha[b];
            if (a >= 0)
              buffer[4] = alpha[a];
            if (ft_strcmp(crypt(buffer, "50"), str) == 0)
            {
              found = 1;
              printf("%s\n", buffer);
            }
            e++;
          }
          d++;
          e = 0;
        }
        c++;
        d = 0;
        e = 0;
      }
      b++;
      c = 0;
      d = 0;
      e = 0;
    }
    a++;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
  }
}

int   main(int argc, char **argv)
{
  if (argc == 2)
  {
    ft_decrypt(argv[1]);
  }
  else
  {
    printf("Usage: ./crack hash\n");
  }
  return (0);
}
