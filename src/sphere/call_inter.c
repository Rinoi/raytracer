/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Sat Jun  8 18:32:02 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

int		is_a_god_sphere(t_obj *obj, t_st *dr, t_inter *inter, int i)
{
  float		a;
  float		b;
  float		c;
  int		x;

  if (is_in_neg(dr->neg, inter->d) == 1)
    {
      if (i == 1)
	return (-1);
      a = pow(dr->vec.x, 2) + pow(dr->vec.y, 2) + pow(dr->vec.z, 2);
      b = 2 * (dr->vec.x * dr->cord.x
	       + dr->vec.y * dr->cord.y + dr->vec.z * dr->cord.z);
      c = pow(dr->cord.x, 2) + pow(dr->cord.y, 2)
	+ pow(dr->cord.z, 2) - pow(*((float *)(obj->data)), 2);
      inter->d = resolve_two_inv(a, b, c, &x);
      inter->cal_norm = sphere_nrml_inv;
      return (is_a_god_sphere(obj, dr, inter, 1));
    }
  return (1);
}

static void	my_sub_vec(t_ptn *cord, t_ptn *obj)
{
  cord->x -= obj->x;
  cord->y -= obj->y;
  cord->z -= obj->z;
}

t_inter		*call_inter_sphere(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  float		a;
  float		b;
  float		c;
  int		x;

  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  my_sub_vec(&obj->ptn, &dr.cord);
  a = pow(dr.vec.x, 2) + pow(dr.vec.y, 2) + pow(dr.vec.z, 2);
  b = 2 * (dr.vec.x * dr.cord.x
	   + dr.vec.y * dr.cord.y + dr.vec.z * dr.cord.z);
  c = pow(dr.cord.x, 2) + pow(dr.cord.y, 2)
    + pow(dr.cord.z, 2) - pow(*((float *)(obj->data)), 2);
  inter->d = resolve_two(a, b, c, &x);
  inter->cal_norm = sphere_nrml;
  inter->status = x;
  if (inter->d <= EPSILLON || is_a_god_sphere(obj, &dr, inter, 0) == -1)
    {
      free(inter);
      return (NULL);
    }
  inter->obj = obj;
  return (inter);
}
