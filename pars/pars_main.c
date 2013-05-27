/*
** pars_main.c for pars_xml in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue Feb 19 22:22:10 2013 lucas mayol
** Last update Sat Apr 13 13:10:51 2013 lucas mayol
*/

#include <stdlib.h>
#include "../include/rtv1.h"
#include "../include/get_next_line.h"
#include "pars.h"

void		my_add_next(t_lb **lb)
{
  t_lb		*elemn;

  if ((elemn = malloc(sizeof(t_lb))) == NULL)
    {
      my_putstr("malloc error\n", 2);
      exit(EXIT_FAILURE);
    }
  if (*lb != NULL)
    {
      my_putstr((*lb)->bal.name, 1);
      my_putchar('\n', 1);
    }
  elemn->next = *lb;
  *lb = elemn;
}

char		*my_take_data_balist(t_rs *rs, int fd, t_lb *lb, char *str)
{
  int		i;
  t_balist	bal;

  bal.name = NULL;
  lb->boll = 1;
  while (bal.name == NULL || my_strcmp(bal.name, lb->bal.name) == 0)
    {
      str = my_go_to_next(rs, str, fd);
      if ((i = what_balist(str, &bal)) == -1)
	my_error(rs, "ballist errore");
      if (bal.name == NULL || my_strcmp(bal.name, lb->bal.name) == 0)
	{
	  my_add_next(&(lb->lb));
	  str = my_pars_act(rs, fd, lb->lb, str);
	}
      else
	str = str + i;
    }
  return (str);
}

char		*my_pars_act(t_rs *rs, int fd, t_lb *lb, char *str)
{
  int 		i;

  lb->bal.name = NULL;
  lb->next = NULL;
  lb->lb = malloc(sizeof(t_lb));
  lb->lb = NULL;
  str = my_go_to_next(rs, str, fd);
  if ((i = what_balist(str, &lb->bal)) == -1)
    my_error(rs, "ballist error");
  str = str + i;
  str = my_go_to_next(rs, str, fd);
  i = epure_to_next(str);
  str = str + i;
  if (*str != '<')
    str = my_take_data(rs, lb, str, fd);
  else
    str = my_take_data_balist(rs, fd, lb, str);
  return (str);
}

void	my_printf_truc(t_lb *lb, int i)
{
  int	u;

  u = 0;
  while (u != i)
    {
      my_putchar(' ', 1);
      u = u + 1;
    }
  my_putstr("name is : ", 1);
  my_putstr(lb->bal.name, 1);
  my_putchar('\n', 1);
  while (lb->lb != NULL)
    {
      my_printf_truc(lb->lb, i + 1);
      lb->lb = lb->lb->next;
    }
}

void		pars_main(t_rs *rs, int fd)
{
  t_balist	bal;
  char		*str;
  t_lb		*lb;

  str = get_next_line(fd);
  rs->l = 1;
  lb = malloc(sizeof(t_lb));
  my_pars_act(rs, fd, lb, str);
  my_putstr("\n\n\n\n", 1);
  my_printf_truc(lb, 0);
}
