/*
** my_lux.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sat May 11 15:18:51 2013 lucas mayol
** Last update Sat May 11 15:39:02 2013 lucas mayol
*/

#include <stdlib.h>
#include "../include/rtv1.h"

unsigned int	my_change_color(unsigned int color, float cos)
{
  unsigned char	*col;

  if (cos > 1)
    return (0);
  col = (unsigned char*)&color;
  col[0] = col[0] * (cos);
  col[1] = col[1] * (cos);
  col[2] = col[2] * (cos);
  col[3] = col[3] * (cos);
  return (color);
}

unsigned int	my_cal_lux(t_rs *rs, t_inter *inter)
{
  unsigned int	color;
  t_lux		*cp;
  float		cos;
  float		cos_m;

  cp = rs->lux;
  color = inter->obj->color;
  cos_m = 0;
  while (cp != NULL)
    {
      cos = inter->obj->cal_lux_cos(inter->obj, &inter->ptn, cp);
      if (cos > cos_m)
	cos_m = cos;
      cp = cp->next;
    }
  color = my_change_color(color, cos_m);
  return (color);
}
