/*
** call_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu May 30 17:28:25 2013 lucas mayol
** Last update Sat Jun  8 19:11:03 2013 lucas mayol
*/

#include <stdio.h>
#include "rt.h"

int	cal_texture_plan(t_obj *obj, float x, float y,
			 __attribute__((unused))float z)
{
  x = (int)x % obj->mat->img.x;
  y = (int)y % obj->mat->img.y;
  if (x < 0)
    x = obj->mat->img.x + x;
  if (y < 0)
    y = obj->mat->img.y + y;
  return (get_col(&obj->mat->img, x, y));
}

float		*my_damier(t_inter *inter, float tab[3], int d)
{
  float		x;
  float		y;

  x = inter->ori_ptn.x > 0 ? inter->ori_ptn.x : (- inter->ori_ptn.x) + d / 2;
  y = inter->ori_ptn.y > 0 ? inter->ori_ptn.y : (- inter->ori_ptn.y) + d / 2;
  if (((int)(x) % d >= (d / 2) && (int)(y) % d < (d / 2)) ||
      ((int)(x) % d < (d / 2) && (int)(y) % d >= (d / 2)))
    {
      tab[0] = 1 - tab[0];
      tab[1] = 1 - tab[1];
      tab[2] = 1 - tab[2];
    }
  return (tab);
}

static float	*color_mat(t_obj *obj, t_inter *inter, float tab[3])
{
  int		color;
  unsigned char	*tabs;

  if (obj->mat->bruit.type != 0)
    {
      color = color_bruit_bois(obj, inter);
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

void		cal_color_plan(t_obj *obj, t_inter *inter, float tab[3])
{
  int		color;
  unsigned char	*tabs;

  tab[0] = 1;
  tab[1] = 1;
  tab[2] = 1;
  if (obj->mat->img.img != NULL)
    {
      color = cal_texture_plan(obj, inter->ptn.x, inter->ptn.y, inter->ptn.z);
      tabs = (unsigned char *)&color;
      tab[0] = (unsigned char)tabs[0] / 255.0;
      tab[1] = (unsigned char)tabs[1] / 255.0;
      tab[2] = (unsigned char)tabs[2] / 255.0;
    }
  else if (obj->mat != NULL)
    {
      if (obj->mat != NULL)
        tab = color_mat(obj, inter, tab);
    }
  if (obj->mat->damier != 0)
    tab = my_damier(inter, tab, obj->mat->damier);
}
