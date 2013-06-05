/*
** cal_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed May 29 21:56:35 2013 lucas mayol
** Last update Wed Jun  5 20:32:03 2013 louis martin-pierrat
*/

#include <stdlib.h>
#include <stdio.h>
#include "rt.h"

int		cal_texture_conus(t_obj *obj, t_ptn inter)
{
  float		x;
  float		y;
  float		pc;
  t_ptn		*mat;

  inter.x -= obj->ptn.x;
  inter.y -= obj->ptn.y;
  inter.z -= obj->ptn.z;
  mat = mul_m_p(obj->matrix, &inter);
  inter.x = mat->x;
  inter.y = mat->y;
  inter.z = mat->z;
  free(mat);

  pc = inter.y;
  x = acos( - (pc / sqrt(pow(inter.x, 2) + pow(inter.y, 2) + pow(inter.z, 2))));
  x =  x / (3.1415);
  x *= obj->mat->img.x;
  
  y = (int)inter.z % obj->mat->img.y;
  if (y < 0)
    y = obj->mat->img.y + y;
  if (y < 0 || x < 0 || x > obj->mat->img.x || y > obj->mat->img.y)
    {
      printf("max %d %d\n", obj->mat->img.x, obj->mat->img.y);
      printf("x %f y %f\n", x, y);
    }
  return (get_col(&obj->mat->img, x, y));
}

void		cal_color_conus(t_obj *obj, t_inter *inter, float tab[3])
{
  int		color;
  unsigned char *tabs;

  if (obj->mat != NULL && obj->mat->img.img != NULL)
    {
      color = cal_texture_conus(obj, inter->ptn);
      tabs = (unsigned char *)&color;
      tab[0] = (unsigned char)tabs[0] / 255.0;
      tab[1] = (unsigned char)tabs[1] / 255.0;
      tab[2] = (unsigned char)tabs[2] / 255.0;
    }
  else
    {
      if (obj->mat != NULL)
	{
	  tab[0] = obj->mat->blue;
	  tab[1] = obj->mat->green;
	  tab[2] = obj->mat->red;
	}
      else
	{
	  tab[0] = 1;
	  tab[1] = 1;
	  tab[2] = 1;
	}
    }
}
