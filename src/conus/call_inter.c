/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Tue May 28 07:47:16 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_inter		*call_inter_conus(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  float		a;
  float		b;
  float		c;
  int		x;
  float		angle;

  angle = ((float *)(obj->data))[0];
  angle = tan(RAD(angle));
  angle = 1 / pow(angle, 2);
  change_dr(obj, &dr);
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  a = pow(dr.vec.x, 2) + pow(dr.vec.y, 2)
  	    - pow(dr.vec.z, 2) * angle * angle;
  b = 2 * (dr.vec.x * dr.cord.x + dr.vec.y * dr.cord.y
  	   - dr.vec.z * dr.cord.z * angle * angle);
  c = pow(dr.cord.x, 2) + pow(dr.cord.y, 2)
    - pow(dr.cord.z, 2) * angle * angle;
  inter->d = resolve_two(a, b, c, &x);
  if (inter->d < 0)
    {
      free(inter);
      return (NULL);
    }
  return (inter);
}
