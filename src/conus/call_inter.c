/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Sat Jun  8 19:01:34 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

int             is_a_god_conus(t_obj *obj, t_st *st, t_inter *inter, int i)
{
  int           x;
  float         a;
  float         b;
  float         c;
  float         angle;

  inter->ptn.x = st->cord.x + st->vec.x * inter->d + obj->ptn.x;
  inter->ptn.y = st->cord.y + st->vec.y * inter->d + obj->ptn.y;
  inter->ptn.z = st->cord.z + st->vec.z * inter->d + obj->ptn.z;
  if ((inter->ptn.z > obj->ptn.z)
      || (inter->ptn.z <= obj->ptn.z - obj->limit_z))
    {
      if (i == 1)
        return (-1);
      angle = ((float *)(obj->data))[0];
      angle = 1 / tan(RAD(angle));
      a = pow(st->vec.x, 2) + pow(st->vec.y, 2)
        - pow(st->vec.z, 2) * angle * angle;
      b = 2 * (st->vec.x * st->cord.x + st->vec.y * st->cord.y
               - st->vec.z * st->cord.z * angle * angle);
      c = pow(st->cord.x, 2) + pow(st->cord.y, 2)
        - pow(st->cord.z, 2) * angle * angle;
      inter->d = resolve_two_inv(a, b, c, &x);
      return (is_a_god_conus(obj, st, inter, 1));
    }
  return (1);
}

t_inter		*put_in_list_inter(t_inter *inter, t_obj *obj, int x)
{
  inter->obj = obj;
  inter->cal_norm = conus_nrml;
  inter->status = x;
  return (inter);
}

t_inter		*call_inter_conus(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  float		a;
  float		b;
  float		c;
  int		x;
  float		angle;

  angle = ((float *)(obj->data))[0];
  angle = 1.0 / tan(RAD(angle));
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
  if (inter->d < 0 || is_a_god_conus(obj, &dr, inter, 0) == -1)
    {
      free(inter);
      return (NULL);
    }
  return (put_in_list_inter(inter, obj, x));
}
