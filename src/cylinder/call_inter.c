/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Tue May 28 05:18:10 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

t_inter		*call_inter_cylinder(t_obj *obj, t_st *dr)
{
  t_inter	*inter;
  float		a;
  float		b;
  float		c;
  int		x;
  
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  a = pow(dr->vec.x, 2) + pow(dr->vec.y, 2);
  b = 2 * (dr->vec.x * dr->cord.x
	   + dr->vec.y * dr->cord.y);
  c = pow(dr->cord.x, 2) + pow(dr->cord.y, 2)
    - pow(*((float *)(obj->data)), 2);
  inter->d = resolve_two(a, b, c, &x);
  if (inter->d == -1)
    {
      free(inter);
      return (NULL);
    }
  return (inter);
}