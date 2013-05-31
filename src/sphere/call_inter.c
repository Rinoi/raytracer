/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Fri May 31 17:17:31 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

t_inter		*call_inter_sphere(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  float		a;
  float		b;
  float		c;
  int		x;
  
  dr.cord.x -= obj->ptn.x;
  dr.cord.y -= obj->ptn.y;
  dr.cord.z -= obj->ptn.z;
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  a = pow(dr.vec.x, 2) + pow(dr.vec.y, 2) + pow(dr.vec.z, 2);
  b = 2 * (dr.vec.x * dr.cord.x
	   + dr.vec.y * dr.cord.y + dr.vec.z * dr.cord.z);
  c = pow(dr.cord.x, 2) + pow(dr.cord.y, 2)
    + pow(dr.cord.z, 2) - pow(*((float *)(obj->data)), 2);
  inter->d = resolve_two(a, b, c, &x);
  if (inter->d < 0)
    {
      free(inter);
      return (NULL);
    }
  inter->cal_norm = sphere_nrml;
  inter->obj = obj;
  inter->rela_ptn.x = dr.cord.x + dr.vec.x * inter->d + obj->ptn.x;
  inter->rela_ptn.y = dr.cord.y + dr.vec.y * inter->d + obj->ptn.y;
  inter->rela_ptn.z = dr.cord.z + dr.vec.z * inter->d + obj->ptn.z;
  return (inter);
}
