/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Sat Jun  8 01:25:28 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

void		change_dr(t_obj *obj, t_st *dr)
{
  t_ptn		*ptn;

  ptn = mul_m_p(obj->matrix, &dr->vec);
  dr->vec.x = ptn->x;
  dr->vec.y = ptn->y;
  dr->vec.z = ptn->z;
  free(ptn);
  dr->cord.x -= obj->ptn.x;
  dr->cord.y -= obj->ptn.y;
  dr->cord.z -= obj->ptn.z;
  ptn = mul_m_p(obj->matrix, &dr->cord);
  dr->cord.x = ptn->x;
  dr->cord.y = ptn->y;
  dr->cord.z = ptn->z;
  free(ptn);
}

int		is_a_god_cylinder(t_obj *obj, t_st *st, t_inter *inter, int i)
{
  int           x;
  float         a;
  float         b;
  float         c;

  inter->ptn.x = st->cord.x + st->vec.x * inter->d;
  inter->ptn.y = st->cord.y + st->vec.y * inter->d;
  inter->ptn.z = st->cord.z + st->vec.z * inter->d;
  inter->ptn.x += obj->ptn.x;
  inter->ptn.y += obj->ptn.y;
  inter->ptn.z += obj->ptn.z;

  if ((inter->ptn.z > obj->ptn.z)
      || (inter->ptn.z < obj->ptn.z - obj->limit_z)
      || is_in_neg(st->neg, inter->d) == 1)
    {
      if (i == 1)
        return (-1);
      a = pow(st->vec.x, 2) + pow(st->vec.y, 2);
      b = 2 * (st->vec.x * st->cord.x
               + st->vec.y * st->cord.y);
      c = pow(st->cord.x, 2) + pow(st->cord.y, 2)
        - pow(*((float *)(obj->data)), 2);
      inter->d = resolve_two_inv(a, b, c, &x);
      inter->cal_norm = cylinder_nrml_inv;
      return (is_a_god_cylinder(obj, st, inter, 1));
    }
  return (1);
}

t_inter		*call_inter_cylinder(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  float		a;
  float		b;
  float		c;
  int		x;
  
  change_dr(obj, &dr);
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  a = pow(dr.vec.x, 2) + pow(dr.vec.y, 2);
  b = 2 * (dr.vec.x * dr.cord.x
	   + dr.vec.y * dr.cord.y);
  c = pow(dr.cord.x, 2) + pow(dr.cord.y, 2)
    - pow(*((float *)(obj->data)), 2);
  inter->d = resolve_two(a, b, c, &x);
  inter->cal_norm = cylinder_nrml;
  if (inter->d == -1)
    {
      free(inter);
      return (NULL);
    }
  if (is_a_god_cylinder(obj, &dr, inter, 0) == -1)
    {
      free(inter);
      return (NULL);
    }
  inter->ptn.x = dr.vec.x * inter->d + dr.cord.x;
  inter->ptn.y = dr.vec.y * inter->d + dr.cord.y;
  inter->ptn.z = dr.vec.z * inter->d + dr.cord.z;
  inter->obj = obj;
  inter->status = x;
  return (inter);
}
