/*
** call_inter.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May  6 12:35:05 2013 lucas mayol
** Last update Sat May 11 23:32:23 2013 lucas mayol
*/

#include <stdlib.h>
#include "../../include/rtv1.h"

static t_ptn	*my_call_point_return(float a, float b, float c,
				      t_st *d)
{
  float		delta;
  t_ptn		*my_return;
  float		k;

  delta = pow(b, 2) - (4.0 * a * c);
  if ((my_return = malloc(sizeof(t_ptn))) == NULL)
    exit(EXIT_FAILURE);
  if (delta < 0)
    {
      free(my_return);
      return (NULL);
    }
  else
    {
      k = (- b - sqrt(delta)) / (2 * a);
      my_return->x = d->cord.x + (k * d->vec.x);
      my_return->y = d->cord.y + (k * d->vec.y);
      my_return->z = d->cord.z + (k * d->vec.z);
    }
  return (my_return);
}

static void	cp_dr(t_st *cp, t_st *d, t_obj *o)
{
  cp->cord.x = d->cord.x - o->ptn.x;
  cp->cord.y = d->cord.y - o->ptn.y;
  cp->cord.z = d->cord.z - o->ptn.z;
  cp->vec.x = d->vec.x;
  cp->vec.y = d->vec.y;
  cp->vec.z = d->vec.z;
}

t_ptn		*my_call_point_shere(t_obj *o, t_st *d)
{
  t_ptn		*my_return;
  t_st		cp;

  cp_dr(&cp, d, o);
  my_return = my_call_point_return(pow(cp.vec.x, 2)
				   + pow(cp.vec.y, 2)
				   + pow(cp.vec.z, 2),
				   2 * (cp.vec.x * cp.cord.x + cp.vec.y *
					cp.cord.y + cp.vec.z * cp.cord.z),
				   pow(cp.cord.x, 2) + pow(cp.cord.y, 2)
				   + pow(cp.cord.z, 2)
				   - pow(o->data[0], 2), d);
  return (my_return);
}
