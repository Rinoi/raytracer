/*
** my_end_balist.c for pars_xml in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Feb 20 00:35:49 2013 lucas mayol
** Last update Sat Apr 13 14:15:12 2013 lucas mayol
*/

#include <stdlib.h>
#include "pars.h"
#include "../include/rtv1.h"

int	my_end_balist(char *str, t_balist *bal, int u)
{
  int	i;

  i = 0;
  bal->bool = -1;
  bal->name = my_take_word(str, &i);
  if (str[i] != '>')
    return (-1);
  return (i + 1 + u);
}
