/*
** what_balist.h for pars_xml in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue Feb 19 22:51:23 2013 lucas mayol
** Last update Sat Apr 13 14:14:51 2013 lucas mayol
*/

#include <stdlib.h>
#include "pars.h"
#include "../include/rtv1.h"

int	is_deb_balist_com(char *str)
{
  if (str[0] != '\0' && str[0] == '!')
    if (str[1] == '\0' && str[1] == '-')
      if (str[2] == '\0' && str[2] == '-')
	return (1);
  return (0);
}

char	*my_take_word(char *str, int *u)
{
  char	*my_return;
  int	i;

  i = *u;
  while (str[i] != ' ' && str[i] != '\t' &&
	 str[i] != '\0' && str[i] != '>' && str[i] != '<')
    i = i + 1;
  if ((my_return = malloc(sizeof(char) * (i - *u + 2))) == NULL)
    {
      my_putstr("malloc error\n", 2);
      exit(EXIT_FAILURE);
    }
  i = 0;
  while (str[*u] != ' ' && str[*u] != '\t' &&
	 str[*u] != '\0' && str[*u] != '>' && str[i] != '<')
    {
      my_return[i] = str[*u];
      i += 1;
      *u += 1;
    }
  my_return[i] = '\0';
  return (my_return);
}

int	my_take_bal_info_act(char *str, t_balist *bal,
			     int u, int i)
{
  while (str[u] != '\0' && str[u] != '>')
    {
      while (str[u] == ' ' || str[u] == '\t')
	u = u + 1;
      if (str[u] != '\0' && str[u] != '>')
	{
	  if (u == 0)
	    bal->name = my_take_word(str, &u);
	  else
	    {
	      bal->arg[i] = my_take_word(str, &u);
	      i = i + 1;
	    }
	}
      while (str[u] == ' ' || str[u] == '\t')
	u = u + 1;
    }
  bal->arg[i] = NULL;
  return (u);
}

int	my_take_bal_info(char *str, t_balist *bal)
{
  int	u;
  int	i;

  u = 0;
  i = 0;
  if ((bal->arg = malloc(sizeof(char*) * (my_str_word(str) + 1))) == NULL)
    {
      my_putstr("malloc error\n", 2);
      exit(EXIT_FAILURE);
    }
  u = my_take_bal_info_act(str, bal, u, i);
  if (str[u] != '>')
    {
      my_putstr("balist no close\n", 2);
      exit(EXIT_FAILURE);
    }
  return (u + 1);
}

int	what_balist(char *str, t_balist *bal)
{
  int	i;

  bal->name = NULL;
  bal->data = NULL;
  i = 0;
  while (str[i] == ' ' || str[i] == '\t')
    i = i + 1;
  if (str[i] == '<')
    i = i + 1;
  else if (str[i] != '\0')
    return (-1);
  else
    {
      my_putstr("lol", 2);
      return (i);
    }
  if (str[i] == '/')
    return (my_end_balist(str + i + 1, bal, i + 1));
  bal->bool = 1;
  if (is_deb_balist_com(str + i) == 1)
    return (-2);
  if ((i += my_take_bal_info(str + i, bal)) == -1)
    return (-1);
  return (i);
}
