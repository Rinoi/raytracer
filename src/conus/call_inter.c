/*
** my_call_point_cone.c for my_call_poin in /home/mayol_l//rt1
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Sun Mar 17 10:41:51 2013 lucas mayol
** Last update Sun May 19 13:18:45 2013 lucas mayol
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../include/rtv1.h"

static t_ptn	*my_call_point_return(float a, float b, float c,
				      t_st *d)
{
  float		delta;
  t_ptn		*my_return;

  delta = b * b - (4 * a * c);
  if ((my_return = malloc(sizeof(t_ptn))) == NULL)
    exit(EXIT_FAILURE);
  if (delta < 0)
    return (NULL);
  else if (delta > 0)
    {
      my_return->x = d->cord.x + (((-b - sqrt(delta)) / (2 * a)) * d->vec.x);
      my_return->y = d->cord.y + (((-b - sqrt(delta)) / (2 * a)) * d->vec.y);
      my_return->z = d->cord.z + (((-b - sqrt(delta)) / (2 * a)) * d->vec.z);
    }
  else
    {
      my_return->x = d->cord.x + (((- b) / (2 * a)) * d->vec.x);
      my_return->y = d->cord.y + (((- b) / (2 * a)) * d->vec.y);
      my_return->z = d->cord.z + (((- b) / (2 * a)) * d->vec.z);
    }
  return (my_return);
}

static void     cp_dr(t_st *cp, t_st *d, t_obj *o)
{
  cp->cord.x = d->cord.x - o->ptn.x;
  cp->cord.y = d->cord.y - o->ptn.y;
  cp->cord.z = d->cord.z - o->ptn.z;
  cp->vec.x = d->vec.x;
  cp->vec.y = d->vec.y;
  cp->vec.z = d->vec.z;
  multipli_x(&cp->vec, -o->rot.x);
}

t_ptn		*my_call_point_conus(t_obj *o, t_st *d)
{
  t_ptn		*my_return;
  t_st		cp;

  cp_dr(&cp, d, o);
  my_return = my_call_point_return(pow(cp.vec.x, 2)
				   + pow(cp.vec.y, 2)
				   - pow(cp.vec.z / pow(tan(RAD(o->data[0])), 2), 2),
				   2 * (cp.vec.x * cp.cord.x
					+ cp.vec.y * cp.cord.y
					- ((cp.cord.z / pow(tan(RAD(o->data[0])), 2))
					   * cp.vec.z)),
				   pow(cp.cord.x, 2)
				   + pow(cp.cord.y, 2)
				   - pow(cp.cord.z / pow(tan(RAD(o->data[0])), 2), 2)
				   , d);
  if (my_return != NULL)
      multipli_x(my_return, o->rot.x);
  if (my_return != NULL && (my_return->z > o->ptn.z))
    {
      free(my_return);
      return (NULL);
    }
  return (my_return);
}
