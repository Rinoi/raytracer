/*
** call_inter.c for RT in /home/mayol_l//git/RayTracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Mon May  6 12:35:05 2013 lucas mayol
** Last update Thu Jun  6 18:45:37 2013 lucas mayol
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "rt.h"

double		find_d(t_obj *o, t_st *dr)
{
  t_tri		*tri;

  tri = (t_tri *)(o->data);
  /* printf("ptn : %f %f %f\n", o->ptn.x, o->ptn.y, o->ptn.z); */
  /* printf("a2 : %f %f %f\na3 %f %f %f\n\n", tri->a2.x, tri->a2.y, tri->a2.z, */
  /* 	 tri->a3.x, tri->a3.y, tri->a3.z); */

  return (-
	  (
	   ( ((tri->a2.y * tri->a3.z) - (tri->a2.z * tri->a3.y))
	     * dr->vec.x)
	   + (  ((tri->a2.z * tri->a3.x) - (tri->a2.x * tri->a3.z))
		* dr->vec.y)
	   + (  ((tri->a2.x * tri->a3.y) - (tri->a2.y * tri->a3.x))
		* dr->vec.z)
	   )
	  );
}

double		find_a(t_obj *o, t_st *dr, double d, t_ptn *w)
{
  t_tri		*tri;

  tri = (t_tri *)(o->data);
  return (
	  ((
	    ( - ((w->y * tri->a3.z) - (w->z * tri->a3.y))
	      * dr->vec.x)
	    + ( - ((w->z * tri->a3.x) - (w->x * tri->a3.z))
		* dr->vec.y)
	    + ( - ((w->x * tri->a3.y) - (w->y * tri->a3.x))
		* dr->vec.z)))
	  / d
	  );
}

double		find_b(t_obj *o, t_st *dr, double d, t_ptn *w)
{
  t_tri		*tri;

  tri = (t_tri *)(o->data);
  return (
	  ((
	    ( - ((tri->a2.y * w->z) - (tri->a2.z * w->y))
	      * dr->vec.x)
	    + ( - ((tri->a2.z * w->x) - (tri->a2.x * w->z))
		* dr->vec.y)
	    + ( - ((tri->a2.x * w->y) - (tri->a2.y * w->x))
		* dr->vec.z)))
	  / d
	  );
}

double		find_t(t_obj *o, double d, t_ptn *w)
{
  t_tri		*tri;

  tri = (t_tri *)(o->data);
  return (
	  ((
	    (((tri->a2.y * tri->a3.z) - (tri->a2.z * tri->a3.y))
	     * w->x)
	    + (((tri->a2.z * tri->a3.x) - (tri->a2.x * tri->a3.z))
	       * w->y)
	    + (((tri->a2.x * tri->a3.y) - (tri->a2.y * tri->a3.x))
	       * w->z)
	    ))
	  / d
	  );
}

t_inter		*call_inter_triangle(t_obj *o, t_st dr)
{
  double	a;
  double	b;
  double	t;
  double	d;
  t_ptn		w;
  t_inter      	*my_return;

  //  printf("triangle time\n");
  w.x = dr.cord.x - o->ptn.x;
  w.y = dr.cord.y - o->ptn.y;
  w.z = dr.cord.z - o->ptn.z;
  if ((d = find_d(o, &dr)) == 0)
    return (NULL);
  a = find_a(o, &dr, d, &w);
  b = find_b(o, &dr, d, &w);
  //  printf("a : %f, b : %f, a + b : %f\n", a, b, a + b);
  if (a >= 0 && b >= 0 /* && a + b <= 1 */)
    {
      /* printf("OK\n"); */
      t = find_t(o, d, &w);
      if ((my_return = malloc(sizeof(t_inter))) == NULL)
	return (NULL);
      my_return->d = t;
      my_return->obj = o;
      my_return->cal_norm = triangle_nrml;
      return (my_return);
    }
  return (NULL);
}
