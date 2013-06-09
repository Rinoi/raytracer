/*
** cal_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed May 29 21:56:35 2013 lucas mayol
** Last update Sun Jun  9 16:29:30 2013 lucas mayol
*/

#include <stdlib.h>
#include <stdio.h>
#include "rt.h"

int		cal_texture_cylinder(t_obj *obj, t_ptn inter)
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
  x = acos(- (pc / sqrt(pow(inter.x, 2) + pow(inter.y, 2) + pow(inter.z, 2))));
  x = (x / (3.1415)) * obj->mat->img.x;
  if (obj->limit_z == 0)
    {
      y = (int)inter.z % obj->mat->img.y;
      if (y < 0)
	y = obj->mat->img.y + y;
    }
  else
    y = (inter.z / (- obj->limit_z)) * obj->mat->img.y;
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

void		cal_color_cylinder(t_obj *obj, t_inter *inter, float tab[3],
				   t_rs *rs)
{
  int		color;
  unsigned char *tabs;

  if (obj->mat->img.img != NULL)
    {
      color = cal_texture_cylinder(obj, inter->ptn);
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
