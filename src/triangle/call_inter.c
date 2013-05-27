/*
** call_inter.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May  6 12:35:05 2013 lucas mayol
** Last update Thu May 16 17:34:51 2013 lucas mayol
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/rtv1.h"

double		find_d(t_obj *o, t_st *dr)
{
  return (-
	  (
	   ( ((o->data[1] * o->data[5]) - (o->data[2] * o->data[4]))
	     * dr->vec.x)
	   + (  ((o->data[2] * o->data[3]) - (o->data[0] * o->data[5]))
		* dr->vec.y)
	   + (  ((o->data[0] * o->data[4]) - (o->data[1] * o->data[3]))
		* dr->vec.z)
	   )
	  );
}

double		find_a(t_obj *o, t_st *dr, double d, t_ptn *w)
{
  return (
	  ((
	    ( - ((w->y * o->data[5]) - (w->z * o->data[4]))
	      * dr->vec.x)
	    + ( - ((w->z * o->data[3]) - (w->x * o->data[5]))
		* dr->vec.y)
	    + ( - ((w->x * o->data[4]) - (w->y * o->data[3]))
		* dr->vec.z)))
	  / d
	  );
}

double		find_b(t_obj *o, t_st *dr, double d, t_ptn *w)
{
  return (
	  ((
	    ( - ((o->data[1] * w->z) - (o->data[2] * w->y))
	      * dr->vec.x)
	    + ( - ((o->data[2] * w->x) - (o->data[0] * w->z))
		* dr->vec.y)
	    + ( - ((o->data[0] * w->y) - (o->data[1] * w->x))
		* dr->vec.z)))
	  / d
	  );
}

double		find_t(t_obj *o, double d, t_ptn *w)
{
  return (
	  ((
	    (((o->data[1] * o->data[5]) - (o->data[2] * o->data[4]))
	     * w->x)
	    + (((o->data[2] * o->data[3]) - (o->data[0] * o->data[5]))
	       * w->y)
	    + (((o->data[0] * o->data[4]) - (o->data[1] * o->data[3]))
	       * w->z)
	    ))
	  / d
	  );
}

t_ptn		*my_call_point_triangle(t_obj *o, t_st *dr)
{
  double	a;
  double	b;
  double	t;
  double	d;
  t_ptn		w;
  t_ptn		*my_return;

  w.x = dr->cord.x - o->ptn.x;
  w.y = dr->cord.y - o->ptn.y;
  w.z = dr->cord.z - o->ptn.z;
  if ((d = find_d(o, dr)) == 0)
    return (NULL);
  a = find_a(o, dr, d, &w);
  b = find_b(o, dr, d, &w);
  if (a >= 0 && b >= 0 && a + b <= 1)
    {
      t = find_t(o, d, &w);
      t = t;
      if ((my_return = malloc(sizeof(t_ptn))) == NULL)
	return (NULL);
      my_return->x = (dr->vec.x * t) + dr->cord.x;
      my_return->y = (dr->vec.y * t) + dr->cord.y;
      my_return->z = (dr->vec.z * t) + dr->cord.z;
      return (my_return);
    }
  return (NULL);
}
