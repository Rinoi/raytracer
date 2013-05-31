/*
** call_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu May 30 17:28:25 2013 lucas mayol
** Last update Thu May 30 18:09:12 2013 lucas mayol
*/

#include <stdio.h>
#include "rt.h"

int	cal_texture_plan(t_obj *obj, float x, float y, float z)
{
  x = (int)x % obj->mat->img.x;
  y = (int)y % obj->mat->img.y;
  if (x < 0)
    x = -x;
  //    x = obj->mat->img.x + x;
  if (y < 0)
    y = -y;
  //y = obj->mat->img.y + y;
  return (get_col(&obj->mat->img, x, y));
}

void		cal_color_plan(t_obj *obj, t_inter *inter, float tab[3])
{
  int		color;
  unsigned char	*tabs;

  if (obj->mat->img.img != NULL)
    {
      color = cal_texture_plan(obj, inter->ptn.x, inter->ptn.y, inter->ptn.z);
      tabs = (char*)&color;
      printf("%x\n", tabs[0]);
      tab[0] = (unsigned char)tabs[0] / 255.0;
      tab[1] = (unsigned char)tabs[1] / 255.0;
      tab[2] = (unsigned char)tabs[2] / 255.0;
    }
  else
    {
      tab[0] = 1;
      tab[1] = 1;
      tab[2] = 1;
    }
}
