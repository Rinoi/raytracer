/*
** call_inter.c for RT in /home/mayol_l//git/raytracer
** 
** Made by lucas mayol
** Login   <mayol_l@epitech.net>
** 
** Started on  Tue May 28 02:57:22 2013 lucas mayol
** Last update Sat Jun  8 00:26:32 2013 lucas mayol
*/

#include <stdlib.h>
#include "rt.h"

/* t_inter		*call_inter_plane(t_obj *obj, t_st dr) */
/* { */
/*   t_inter	*inter; */

/*   change_dr(obj, &dr); */
/*   if ((inter = malloc(sizeof(t_inter))) == NULL) */
/*     return (NULL); */
/*   if ((dr.vec.z == 0 && dr.vec.z != obj->ptn.z) || */
/*       (obj->ptn.z < dr.cord.z && dr.vec.z > 0) || */
/*       (obj->ptn.z > dr.cord.z && dr.vec.z < 0)) */
/*     { */
/*       free(inter); */
/*       return (NULL); */
/*     } */
/*   if (dr.vec.z == 0) */
/*     inter->d = EPSILLON; */
/*   else */
/*     inter->d = - dr.cord.z / dr.vec.z; */
/*   if (inter->d <= EPSILLON) */
/*     { */
/*       free(inter); */
/*       return (NULL); */
/*     } */
/*   inter->obj = obj; */
/*   inter->cal_norm = plane_nrml_inv; */
/*   if (dr.cord.z > obj->ptn.z) */
/*     inter->cal_norm = plane_nrml; */
/*   inter->ptn.x = dr.cord.x + dr.vec.x * inter->d; */
/*   inter->ptn.y = dr.cord.y + dr.vec.y * inter->d; */
/*   inter->ptn.z = dr.cord.z + dr.vec.z * inter->d; */
/*   return (inter); */
/* } */

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
  return (inter);
}
