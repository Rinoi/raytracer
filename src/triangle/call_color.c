/*
** call_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu May 30 17:28:25 2013 lucas mayol
** Last update Sat Jun  8 19:13:37 2013 lucas mayol
*/

#include <stdio.h>
#include "rt.h"

void		call_color_triangle(__attribute__((unused))t_obj *obj,
				    __attribute__((unused))t_inter *inter,
				    float tab[3])
{
  tab[0] = 1;
  tab[1] = 1;
  tab[2] = 1;
}
