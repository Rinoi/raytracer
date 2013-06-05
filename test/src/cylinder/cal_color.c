/*
** cal_color.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Wed May 29 21:56:35 2013 lucas mayol
** Last update Sat Jun  1 01:39:27 2013 karina martynava
*/

#include <stdio.h>
#include "rt.h"

int		cal_texture_cylinder(t_obj *obj, float x, float y, float z)
{
  float		pc;
  float		a;

  x -= obj->ptn.x;
  y -= obj->ptn.y;
  z -= obj->ptn.z;
  pc = y;
  a = acos(pc / (sqrt((y * y) + (x * x))));
  printf("angle : %f\n", a);
  a = a / (2.0 * 3.14150);
  printf("%f%%\n", a);
  a *= (obj->mat->img.x - 1);
  printf("a : %f\n", a);
  z = (int)z % (obj->mat->img.y - 1);
  if (z < 0)
    z = -z;
  return (get_col(&obj->mat->img, a, z));
}

void		cal_color_cylinder(t_obj *obj, __attribute__((unused))t_inter *inter, float tab[3])
{
  /* int		color; */
  /* char		*tabs; */

  /* if (obj->mat->img.img != NULL) */
  /*   { */
  /*     color = cal_texture_cylinder(obj, inter->rela_ptn.x, inter->rela_ptn.y, inter->rela_ptn.z); */
  /*     printf("color : %X\n", color); */
  /*     tabs = (char*)&color; */
  /*     printf("les petit valeur :\n%d %d %d\n", tabs[0], tabs[1], tabs[2]); */
  /*     tab[0] = (float)tabs[0] / 255.0; */
  /*     tab[1] = (float)tabs[1] / 255.0; */
  /*     tab[2] = (float)tabs[2] / 255.0; */
  /*     printf("r : %f, g : %f, b : %f\n", tab[0], tab[1], tab[2]); */
  /*     printf("END\n\n\n"); */
  /*   } */
  /* else */
  /*   { */
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
