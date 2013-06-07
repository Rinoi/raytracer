/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Sat Jun  8 01:25:21 2013 karina martynava
*/

#include <stdlib.h>
#include "rt.h"

t_inter		*call_inter_plane(t_obj *obj, t_st dr)
{
  t_inter	*inter;
  float		c;

  change_dr(obj, &dr);
  c = *(float *)(obj->data);
  if ((c < 0 && dr.vec.z > 0) ||
      (c > 0 && dr.vec.z < 0) ||
      dr.vec.z == 0)
    return (NULL);
  if ((inter = malloc(sizeof(t_inter))) == NULL)
    exit(EXIT_FAILURE);
  inter->d = (c - dr.cord.z) / dr.vec.z;
  if (is_in_neg(dr.neg, inter->d) == 1)
    {
      free(inter);
      return (NULL);
    }
  inter->cal_norm = plane_nrml;
  if (c - dr.cord.z > obj->ptn.z)
    inter->cal_norm = plane_nrml_inv;
  //  printf("PLAN\n");
  inter->obj = obj; 
  inter->status = 2;
 return (inter);
}
