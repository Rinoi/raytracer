/*
** call_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu May 30 17:28:25 2013 lucas mayol
** Last update Sun Jun  9 14:31:11 2013 karina martynava
*/

#include <stdio.h>
#include "rt.h"

static float	*color_mat(t_obj *obj, t_inter *inter, float tab[3], t_rs *rs)
{
  int		color;
  unsigned char	*tabs;

  if (obj->mat->bruit.type != 0)
    {
      color = color_bruit_bois(obj, inter, rs);
      tabs = (unsigned char *)&color;
      tab[0] = (unsigned char)tabs[0] / 255.0;
      tab[1] = (unsigned char)tabs[1] / 255.0;
      tab[2] = (unsigned char)tabs[2] / 255.0;
    }
  else
    {
      tab[0] = obj->mat->blue;
      tab[1] = obj->mat->green;
      tab[2] = obj->mat->red;
    }
  return (tab);
}

void		call_color_triangle(t_obj *obj,
				    t_inter *inter,
				    float tab[3], t_rs *rs)
{
  if (obj->mat != NULL)
    tab = color_mat(obj, inter, tab, rs);
  else
    {
      tab[0] = 1;
      tab[1] = 1;
      tab[2] = 1;
    }
}
