/*
** my_error.c for pars_xml in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed Feb 20 00:08:15 2013 lucas mayol
** Last update Sat Apr 13 14:13:37 2013 lucas mayol
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/rtv1.h"
#include "../include/get_next_line.h"
#include "pars.h"

void	my_error( __attribute__((unused)) t_rs *rs, char *str)
{
  my_putstr("error ", 2);
  my_putstr(str, 2);
  my_putchar('\n', 2);
  exit(EXIT_FAILURE);
}
