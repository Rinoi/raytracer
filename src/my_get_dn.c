/*
** my_get_dn.c for rtv1 in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat Feb 23 17:57:00 2013 lucas mayol
** Last update Sun Apr 14 23:30:27 2013 lucas mayol
*/

#include <stdlib.h>
#include "../include/rtv1.h"

float	my_get_dn(char *str, char *name)
{
  if (str == NULL)
    {
      my_putstr("absence of value on : ", 2);
      my_putstr(name, 2);
      my_putchar('\n', 2);
      exit(EXIT_FAILURE);
    }
  return (my_getfloat(str));
}
