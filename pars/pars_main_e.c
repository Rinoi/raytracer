/*
** pars_main_e.c for pars_m in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sun Mar 17 11:26:01 2013 lucas mayol
** Last update Sat Apr 13 13:57:02 2013 lucas mayol
*/

#include <stdlib.h>
#include "../include/rtv1.h"
#include "../include/get_next_line.h"
#include "pars.h"

int	epure_to_next(char *str)
{
  int	i;

  i = 0;
  while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
    i = i + 1;
  return (i);
}

char	*my_go_to_next(t_rs *rs, char *str, int fd)
{
  while (*str == '\0' || *str == '\n')
    {
      str = get_next_line(fd);
      if (str == NULL)
        my_error(rs, "end of file");
      rs->l += 1;
    }
  return (str);
}

char		*my_take_data(t_rs *rs, t_lb *lb, char *str, int fd)
{
  int		i;
  t_balist	bal;

  i = 0;
  lb->boll = 2;
  lb->data = my_take_word(str, &i);
  str = str + i;
  str = my_go_to_next(rs, str, fd);
  if ((i = what_balist(str, &bal)) == -1)
    my_error(rs, "ballist errors");
  if (my_strcmp(bal.name, lb->bal.name) == 0 || bal.bool != -1)
    my_error(rs, "no close balist");
  str = str + i;
  return (str);
}
