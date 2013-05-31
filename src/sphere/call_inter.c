/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Sat Jun  1 00:24:49 2013 karina martynava
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
  
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  dr.cord.x -= obj->ptn.x;
  dr.cord.y -= obj->ptn.y;
  dr.cord.z -= obj->ptn.z;
  a = pow(dr.vec.x, 2) + pow(dr.vec.y, 2) + pow(dr.vec.z, 2);
  b = 2 * (dr.vec.x * dr.cord.x
	   + dr.vec.y * dr.cord.y + dr.vec.z * dr.cord.z);
  c = pow(dr.cord.x, 2) + pow(dr.cord.y, 2)
    + pow(dr.cord.z, 2) - pow(*((float *)(obj->data)), 2);
  inter->d = resolve_two(a, b, c, &x);
  if (inter->d <= EPSILLON)
    {
      free(inter);
      return (NULL);
    }
  inter->cal_norm = sphere_nrml;
  inter->obj = obj;
  inter->rela_ptn.x = dr.vec.x * inter->d + dr.cord.x + obj->ptn.x;
  inter->rela_ptn.y = dr.vec.y * inter->d + dr.cord.y + obj->ptn.y;
  inter->rela_ptn.z = dr.vec.z * inter->d + dr.cord.z + obj->ptn.z;
  return (inter);
}
