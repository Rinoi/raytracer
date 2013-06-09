/*
** wrd_tab.c for minishell un in /home/martyn_k//Project/UNIX/Minishell/code
** 
** Made by karina martynava
** Login   <martyn_k@epitech.net>
** 
** Started on  Sat Dec 15 10:37:43 2012 karina martynava
** Last update Sun Jun  9 09:22:16 2013 karina martynava
*/

#include <stdlib.h>
#include <unistd.h>

int  wrd_cnt(char *str, char c)
{
  int  i;
  int  wrd;

  wrd = 0;
  i = 0;
  while (str[i] == c)
    i++;
  while (str[i] != '\0')
    {
      if (str[i] != '\0' && str[i] != c && str[i] != '\t' && str[i] != '\n')
	wrd++;
      while (str[i] != '\0' && str[i] != c && str[i] != '\t' && str[i] != '\n')
	i++;
      while (str[i] == c || str[i] == '\t' || str[i] == '\n')
	i++;
    }
  return (wrd);
}

char  *wrd_cpy(char *str, int *i, char c)
{
  char  *cpy;
  int  j;

  j = 0;
  while (str[(*i) + j] != '\0' && str[(*i) + j] != c)
    j++;
  if ((cpy = malloc(sizeof(*cpy) * (j + 1))) == NULL)
    return (NULL);
  j = 0;
  while (str[(*i)] != '\0' && str[(*i)] != c &&
	 str[(*i)] != '\t' && str[(*i)] != '\n')
    {
      cpy[j++] = str[(*i)];
      *i = *i + 1;
    }
  cpy[j] = '\0';
  return (cpy);
}

char  **wrd_tab(char *str, char c)
{
  int  i;
  int  wrd;
  int  wrdcnt;
  char  **tab;
  int  j;

  j = 0;
  wrd = 0;
  i = 0;
  if (str == NULL)
    return (NULL);
  wrdcnt = wrd_cnt(str, c);
  if (wrdcnt == 0 || (tab = malloc(sizeof(*tab) * (wrdcnt + 1))) == NULL)
    return (NULL);
  tab[wrdcnt] = NULL;
  while (wrd++ < wrdcnt)
    {
      while (str[i] == c || str[i] == '\t' || str[i] == '\n')
	i++;
      if ((tab[j] = wrd_cpy(str, &i, c)) == NULL)
	return (NULL);
      j++;
    }
  return (tab);
}
