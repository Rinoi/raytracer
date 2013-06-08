/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Sat Jun  8 18:34:36 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

/* int		is_a_god_sphere(t_obj *obj, t_st *dr, t_inter *inter, int i) */
/* { */
/*   float		a; */
/*   float		b; */
/*   float		c; */
/*   int		x; */

/*   if (is_in_neg(dr->neg, inter->d) == 1) */
/*     { */
/*       if (i == 1) */
/* 	return (-1); */
/*       a = pow(dr->vec.x, 2) + pow(dr->vec.y, 2) + pow(dr->vec.z, 2); */
/*       b = 2 * (dr->vec.x * dr->cord.x */
/* 	       + dr->vec.y * dr->cord.y + dr->vec.z * dr->cord.z); */
/*       c = pow(dr->cord.x, 2) + pow(dr->cord.y, 2) */
/* 	+ pow(dr->cord.z, 2) - pow(*((float *)(obj->data)), 2); */
/*       inter->d = resolve_two_inv(a, b, c, &x); */
/*       inter->cal_norm = sphere_nrml_inv; */
/*       return (is_a_god_sphere(obj, dr, inter, 1)); */
/*     } */
/*   return (1); */
/* } */

t_inter		*call_inter_tore(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  float		eq[5];
  int		x;
  float		w;
  float		y;
  float		z;
  float		big_r;
  float		r;
  float		*param;

  param = ((float *)(obj->data));
  big_r = param[0];
  r = param[1];
  printf("%f %f\t", big_r, r);
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    return (NULL);
  w = pow(dr.vec.x, 2) + pow(dr.vec.y, 2) + pow(dr.vec.z, 2);
  y = pow(dr.cord.x, 2) + pow(dr.cord.y, 2) + pow(dr.cord.z, 2)
    + pow(big_r, 2) - pow(r, 2);
  z = dr.vec.y * dr.cord.y + dr.vec.z * dr.cord.z + dr.vec.x * dr.cord.x;
  eq[4] = pow(w, 2);
  eq[3] = 4 * w * z;
  eq[2] = 2 * w * y + pow(z, 2) - 4 * pow(big_r, 2) * (pow(dr.vec.x, 2) + pow(dr.vec.z, 2));
  eq[1] = 4 * z * y - 8 * pow(big_r, 2) * (dr.vec.z * dr.cord.z + dr.vec.x * dr.cord.x);
  eq[0] = pow(y, 2) - 4 * pow(big_r, 2) * (pow(dr.cord.x, 2) + pow(dr.cord.z, 2));
  inter->d = resolve_four(eq, &x);
  if (inter->d != MAXFLOAT)
    printf("%f\n",   inter->d);
  inter->cal_norm = sphere_nrml;
  inter->status = x % 2;
  if (inter->d <= EPSILLON || inter->d == MAXFLOAT)
    {
      free(inter);
      return (NULL);
    }
  inter->obj = obj;
  return (inter);
}
