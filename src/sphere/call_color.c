/*
** call_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Thu May 30 17:28:25 2013 lucas mayol
** Last update Sun Jun  9 14:29:49 2013 karina martynava
*/

#include <stdio.h>
#include "rt.h"

int	cal_texture_sphere(t_obj *obj, t_ptn inter)
{
  float	x;
  float	y;
  float	pc;

  inter.x -= obj->ptn.x;
  inter.y -= obj->ptn.y;
  inter.z -= obj->ptn.z;

  pc = inter.y;
  x = acos(- (pc / sqrt(pow(inter.x, 2) + pow(inter.y, 2) + pow(inter.z, 2))));
  x =  x / (3.1415);
  x *= obj->mat->img.x;

  pc = inter.z;
  y = acos(- (pc / sqrt(pow(inter.x, 2) + pow(inter.y, 2) + pow(inter.z, 2))));
  y = y / (3.1415);
  y *= obj->mat->img.y;
  if (y < 0 || x < 0)
    {
      printf("max %d %d\n", obj->mat->img.x, obj->mat->img.y);
      printf("x %f y %f\n", x, y);
    }
  return (get_col(&obj->mat->img, x, y));
}

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

void		cal_color_shere(t_obj *obj, t_inter *inter, float tab[3], t_rs *rs)
{
  int		color;
  unsigned char	*tabs;

  if (obj->mat != NULL && obj->mat->img.img != NULL)
    {
      color = cal_texture_sphere(obj, inter->ptn);
      tabs = (unsigned char *)&color;
      tab[0] = (unsigned char)tabs[0] / 255.0;
      tab[1] = (unsigned char)tabs[1] / 255.0;
      tab[2] = (unsigned char)tabs[2] / 255.0;
    }
  else
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
}
