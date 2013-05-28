/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Tue May 28 23:02:58 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

void		change_dr(t_obj *obj, t_st *dr)
{
  t_ptn		*ptn;

  //  printf("ANC %f, %f, %f\n", dr->vec.x, dr->vec.y, dr->vec.z);
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
  // printf("NEW %f, %f, %f\n\n", dr->vec.x, dr->vec.y, dr->vec.z);
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
  if (inter->d == -1)
    {
      free(inter);
      return (NULL);
    }
  inter->cal_norm = cylinder_nrml;
  return (inter);
}
